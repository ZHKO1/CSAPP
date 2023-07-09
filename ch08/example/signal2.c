#include "../../lib/csapp.h"

void handler1(int sig)
{
  int olderrno = errno;
  if (waitpid(-1, NULL, 0) < 0)
  {
    sio_error("waitpid error");
  }
  Sio_puts("Handler reaped child\n");
  Sleep(1);
  errno = olderrno;
}

void handler2(int sig)
{
  int olderrno = errno;
  Sio_puts("handler2 start\n");
  while (waitpid(-1, NULL, 0) > 0)
  {
    Sio_puts("Handler reaped child\n");
  }
  if (errno != ECHILD)
    sio_error("waitpid error");

  Sleep(1);
  errno = olderrno;
  Sio_puts("handler2 end\n");
}

int main(int argc, char *argv[], char *envp[])
{
  int i, n;
  char buf[MAXBUF];

  if (signal(SIGCHLD, handler2) == SIG_ERR)
    unix_error("signal error");

  for (i = 0; i < 3; i++)
  {
    if (Fork() == 0)
    {
      printf("Hello from child %d\n", (int)getgid());
      exit(0);
    }
  }

  if (n = read(STDIN_FILENO, buf, sizeof(buf) < 0))
    unix_error("read");

  printf("Parent processing input\n");
  while (1)
    ;
  exit(0);
}