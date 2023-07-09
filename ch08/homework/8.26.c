#include "../../lib/csapp.h"
#include <assert.h>
#define MAXARGS 128
#define MAXJOBS 100

/**
 * 具体请以shell lab为准
 * 此代码存在各种问题，仅供参考
 */

struct job
{
  unsigned int id;
  pid_t pid;
  char *cmd;
  /**
   * 0: Running
   * 1: Stopped
   * 2: Terminated
   */
  int status;
};

void eval(char *cmdline);
void parseline(char *buf, char **argv, int *bg);
int builtin_command(char **argv);
void command_bg(char **argv);
void command_fg(char **argv);
int get_argv_len(char **argv);

void check_parseline(int bg, char **argv);

void add_job(pid_t pid, char *cmd);
void delete_job(pid_t pid);
struct job *get_job_by_id(int id);
struct job *get_job_by_pid(pid_t pid);
void show_jobs();
void show_job_by_pid(pid_t pid);
void show_job(struct job *jptr);
void show_job_terminated_by_sig(pid_t pid, int sig);

void chld_handler(int sig);
void int_handler(int sig);
void tstp_handler(int sig);

struct job *job_list[MAXJOBS] = {NULL};

unsigned int ID = 0;
pid_t pid_current = 0;
sigset_t MASK, PREV;

int main()
{
  char cmdline[MAXLINE];
  Sigemptyset(&MASK);
  Sigaddset(&MASK, SIGCHLD);
  Sigaddset(&MASK, SIGINT);
  // Sigaddset(&MASK, SIGTSTP);

  Signal(SIGCHLD, chld_handler);
  Signal(SIGINT, int_handler);
  Signal(SIGTSTP, tstp_handler);
  while (1)
  {
    // fflush(stdin);
    Sigprocmask(SIG_BLOCK, &MASK, &PREV);
    // Sio_puts("set chld mask\n");
    printf("> ");
    Fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin))
      exit(0);

    eval(cmdline);
    Sigprocmask(SIG_SETMASK, &PREV, NULL);
    // Sio_puts("unset chld mask\n");
  }
}

void eval(char *cmdline)
{
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int bg = 0;
  pid_t pid;

  strcpy(buf, cmdline);
  parseline(buf, argv, &bg);

  // check_parseline(bg, argv);

  if (argv[0] == NULL)
    return;

  if (!builtin_command(argv))
  {
    if (((pid = Fork()) == 0))
    {
      int r;
      Sigprocmask(SIG_SETMASK, &PREV, NULL);
      Setpgid(pid, pid);
      if ((r = execve(argv[0], argv, environ)) < 0)
      {
        printf("%s: Command not found.\n", argv[0]);
        exit(0);
      }
    }
    add_job(pid, cmdline);
    // show_jobs();
    if (!bg)
    {
      pid_current = pid;
      Sigsuspend(&PREV);
      pid_current = 0;
    }
    else
    {
      show_job_by_pid(pid);
    }
  }
}

void parseline(char *buf, char **argv, int *bg)
{
  char *delim;
  int argc;

  buf[strlen(buf) - 1] = ' ';
  while (*buf && (*buf == ' '))
    buf++;

  argc = 0;
  while (delim = strchr(buf, ' '))
  {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' '))
      buf++;
  }
  argv[argc] = NULL;

  if (argc == 0)
    return;

  char *last_arg = argv[argc - 1];
  if ((strlen(last_arg) == 1) && (last_arg[0] == '&'))
  {
    *bg = 1;
    argv[--argc] = NULL;
  }
}

int builtin_command(char **argv)
{
  if (!strcmp(argv[0], "quit"))
    exit(0);
  if (!strcmp(argv[0], "jobs"))
  {
    show_jobs();
    return 1;
  }
  if (!strcmp(argv[0], "bg"))
  {
    command_bg(argv);
    return 1;
  }
  if (!strcmp(argv[0], "fg"))
  {
    command_fg(argv);
    return 1;
  }
  if (!strcmp(argv[0], "&"))
    return 1;
  return 0;
}

void command_bg(char **argv)
{
  int len = get_argv_len(argv);
  if (len != 2)
  {
    Sio_puts("[usage] bg %%${jobid}\n");
    Sio_puts("[usage] bg ${pid}\n");
    return;
  }
  struct job *jptr = NULL;
  if (*argv[1] == '%')
  {
    int id;
    sscanf(argv[1], "%%%d", &id);
    jptr = get_job_by_id(id);
  }
  else
  {
    int pid;
    sscanf(argv[1], "%d", &pid);
    jptr = get_job_by_pid(pid);
  }
  if (jptr == NULL)
  {
    printf("[%s]: No such process\n", argv[1]);
    return;
  }
  int id = jptr->id;
  int status = jptr->status;
  int pid = jptr->pid;
  if (status == 0)
  {
    printf("job %d already in background\n", id);
    return;
  }
  else if (status == 1)
  {
    Kill(pid, SIGCONT);
    Sigsuspend(&PREV);
    show_job_by_pid(pid);
  }
  else
  {
    printf("job %d already terminated\n", id);
  }
}

void command_fg(char **argv)
{
  int len = get_argv_len(argv);
  if (len != 2)
  {
    Sio_puts("[usage] fg %%${jobid}\n");
    Sio_puts("[usage] fg ${pid}\n");
    return;
  }
  struct job *jptr = NULL;
  if (*argv[1] == '%')
  {
    int id;
    sscanf(argv[1], "%%%d", &id);
    jptr = get_job_by_id(id);
  }
  else
  {
    int pid;
    sscanf(argv[1], "%d", &pid);
    jptr = get_job_by_pid(pid);
  }
  if (jptr == NULL)
  {
    printf("[%s]: No such process\n", argv[1]);
    return;
  }
  int id = jptr->id;
  int status = jptr->status;
  int pid = jptr->pid;
  if (status == 0)
  {
    pid_current = pid;
    Sigsuspend(&PREV);
    pid_current = 0;
    return;
  }
  else if (status == 1)
  {
    Kill(pid, SIGCONT);
    Sigsuspend(&PREV);
    pid_current = pid;
    Sigsuspend(&PREV);
    pid_current = 0;
    return;
  }
  else
  {
    printf("job %d already terminated\n", id);
  }
}

int get_argv_len(char **argv)
{
  int i = 0;
  char *env = NULL;
  while ((env = argv[i]) != NULL)
    i++;
  return i;
}

void check_parseline(int bg, char **argv)
{
  int i = 0;
  char *env = NULL;
  printf("bg = %d\n", bg);
  while (env = argv[i++])
  {
    printf("argv[%d]: %s\n", i, env);
  };
}

void add_job(pid_t pid, char *cmd)
{
  unsigned int id = ID++;
  int i = 0;

  char *str = (char *)malloc((sizeof(strlen(cmd) + 1)));
  strcpy(str, cmd);
  struct job *j = (struct job *)malloc((sizeof(struct job)));
  j->id = id;
  j->pid = pid;
  j->cmd = str;

  // j.status = 0;

  while (job_list[i] != NULL)
  {
    i++;
  }
  job_list[i] = j;
  job_list[i + 1] = NULL;
}

void delete_job(pid_t pid)
{
  int i = 0;
  struct job *jptr = NULL;
  while ((jptr = job_list[i]) != NULL)
  {
    pid_t jptr_pid = jptr->pid;
    if (jptr_pid == pid)
    {
      break;
    }
    i++;
  }
  assert(jptr->pid == pid);
  int i_next = i + 1;
  while ((jptr = job_list[i_next]) != NULL)
  {
    job_list[i_next - 1] = jptr;
    i_next++;
  }
  job_list[i_next - 1] = NULL;
}

struct job *get_job_by_id(int id)
{
  int i = 0;
  struct job *jptr = NULL;
  while ((jptr = job_list[i]) != NULL)
  {
    if (jptr->id == id)
    {
      return jptr;
    }
    i++;
  }
  return jptr;
}

struct job *get_job_by_pid(pid_t pid)
{
  int i = 0;
  struct job *jptr = NULL;
  while ((jptr = job_list[i]) != NULL)
  {
    if (jptr->pid == pid)
    {
      return jptr;
    }
    i++;
  }
  return jptr;
}

void show_jobs()
{
  int i = 0;
  struct job *jptr = NULL;
  while ((jptr = job_list[i]) != NULL)
  {
    show_job(jptr);
    i++;
  }
}

void show_job_by_pid(pid_t pid)
{
  int i = 0;
  struct job *jptr = NULL;
  while ((jptr = job_list[i]) != NULL)
  {
    if (jptr->pid == pid)
    {
      show_job(jptr);
      break;
    }
    i++;
  }
}

void show_job(struct job *jptr)
{
  char str[100] = "";
  switch (jptr->status)
  {
  case 0:
    strcpy(str, "Running");
    break;
  case 1:
    strcpy(str, "Stopped");
    break;
  case 2:
    strcpy(str, "Terminated");
    break;
  }
  printf("[%d] %d %s %s", jptr->id, jptr->pid, str, jptr->cmd);
}

void show_job_terminated_by_sig(pid_t pid, int sig)
{
  char str[200] = "";
  sprintf(str, "Job [%d] terminated by signal", pid);
  psignal(sig, str);
}

void chld_handler(int sig)
{
  int olderrno = errno;
  sigset_t mask_all, prev_all;
  Sigfillset(&mask_all);
  Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
  // Sio_puts("get chld Sign\n");
  for (int i = 0; job_list[i] != NULL; i++)
  {
    struct job *jptr = job_list[i];
    pid_t pid = jptr->pid;
    int status;
    pid_t r = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);
    if (r)
    {
      if (WIFEXITED(status))
      {
        delete_job(pid);
        i--;
        continue;
      }
      if (WIFSIGNALED(status))
      {
        int sig = WTERMSIG(status);
        show_job_terminated_by_sig(pid, sig);
        delete_job(pid);
        i--;
        continue;
      }
      if (WIFSTOPPED(status))
      {
        int sig = WSTOPSIG(status);
        show_job_terminated_by_sig(pid, sig);
        jptr->status = 1;
        continue;
      }
      if (WIFCONTINUED(status))
      {
        jptr->status = 0;
        continue;
      }
    }
    // show_job_by_pid(pid);
  }
  Sigprocmask(SIG_SETMASK, &prev_all, NULL);

  errno = olderrno;
}

void int_handler(int sig)
{
  // Sio_puts("int_handler\n");
  if (pid_current)
  {
    // Sio_puts("kill int\n");
    Kill(pid_current, SIGINT);
    Sigsuspend(&PREV);
  }
}

void tstp_handler(int sig)
{
  // Sio_puts("tstp_handler\n");
  if (pid_current)
  {
    // Sio_puts("kill tstp\n");
    Kill(pid_current, SIGTSTP);
    Sigsuspend(&PREV);
  }
}