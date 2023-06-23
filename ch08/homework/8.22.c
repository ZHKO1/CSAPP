#include "../lib/csapp.h"
#include <stdlib.h>

/*
  这里有点奇怪 异常也是走的WIFEXITED(status)
*/

int mysystem(char *command)
{
  if ((strlen(command) == 0) || (command == NULL))
  {
    fprintf(stderr, "mysystem command error %s\n", command);
    exit(1);
  }

  int pid;
  if ((pid = Fork()) == 0)
  {
    char *argv[] = {};
    argv[0] = "/bin/sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = NULL;
    if (execve("/bin/sh", argv, environ) < 0)
    {
      fprintf(stderr, "execve error\n");
      exit(1);
    }
  }

  int retpid;
  int status;
  if ((retpid = Waitpid(pid, &status, 0)) > 0)
  {
    if (WIFEXITED(status))
    {
      int exit_status = WEXITSTATUS(status);
      printf("child %d terminated normally with exit status=%d\n", retpid, exit_status);
      return exit_status;
    }
    if (WIFSIGNALED(status))
    {
      int exit_status = WTERMSIG(status);
      printf("child %d terminated abnormally with exit status=%d\n", retpid, exit_status);
      return exit_status;
    }
    printf("child %d terminated ???\n", retpid);
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[], char *envp[])
{
  if (argc != 2)
  {
    printf("argc must be 2\n");
    return 0;
  }

  char *command = argv[1];
  int status = mysystem(command);
  printf("status = %d\n", status);

  return 0;
}