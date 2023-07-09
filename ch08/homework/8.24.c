#include "../../lib/csapp.h"
#define N 2

int main()
{
  int status, i;
  pid_t pid;

  for (i = 0; i < N; i++)
    if ((pid = Fork()) == 0)
    {
      char *dst = NULL;
      char *src = "FUCK";
      strcpy(dst, src);
      exit(100 + i);
    }

  i = 0;
  while ((pid = waitpid(-1, &status, 0)) > 0)
  {
    int exit_status;
    if (WIFSIGNALED(status))
    {
      exit_status = WTERMSIG(status);
      char str[200] = "";
      sprintf(str, "child %d terminated by signal %d", pid, exit_status);
      psignal(exit_status, str);
    }
    else
    {
      printf("child %d terminated ???\n", pid);
    }
  }

  if (errno != ECHILD)
    unix_error("waitpid error");

  exit(0);
}