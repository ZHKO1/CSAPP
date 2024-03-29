#include "../../lib/csapp.h"
#define MAXARGS 128

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

void check_parseline(int bg, char **argv);

int main()
{
  char cmdline[MAXLINE];
  while (1)
  {
    printf("> ");
    Fgets(cmdline, MAXLINE, stdin);
    if (feof(stdin))
      exit(0);

    eval(cmdline);
  }
}

void eval(char *cmdline)
{
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int bg;
  pid_t pid;

  strcpy(buf, cmdline);
  bg = parseline(buf, argv);
  // check_parseline(bg, argv);

  if (argv[0] == NULL)
    return;

  if (!builtin_command(argv))
  {
    if (((pid = Fork()) == 0))
    {
      int r;
      if ((r = execve(argv[0], argv, environ)) < 0)
      {
        printf("%s: Command not found.\n", argv[0]);
        exit(0);
      }

      // execve 成功情况下从不返回，失败则返回-1
      printf("---- execve return %d\n", r);
    }

    if (!bg)
    {
      int status;
      if (waitpid(pid, &status, 0) < 0)
        unix_error("waitfg: waitpid error");
    }
    else
      printf("%d %s", pid, cmdline);
  }
}

int parseline(char *buf, char **argv)
{
  char *delim;
  int argc;
  int bg;

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
    return 1;

  if ((bg = (*argv[argc - 1] == '&') != 0))
    argv[--argc] = NULL;

  return bg;
}

int builtin_command(char **argv)
{
  if (!strcmp(argv[0], "quit"))
    exit(0);
  if (!strcmp(argv[0], "&"))
    return 1;
  return 0;
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