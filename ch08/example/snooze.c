#include "../../lib/csapp.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig)
{
  printf("\nCtrl + C\n");
  return;
}

unsigned int snooze(unsigned int secs)
{
  unsigned r = sleep(secs);
  printf("Slept for %d of %d secs\n", secs - r, secs);
  return r;
}

int main(int argc, char *argv[], char *envp[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <secs>\n", argv[0]);
    exit(0);
  }

  if (signal(SIGINT, sigint_handler) == SIG_ERR)
  {
    unix_error("signal error");
  }

  int r = snooze(atoi(argv[1]));
  return 0;
}