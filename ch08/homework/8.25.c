#include "../lib/csapp.h"
#define LEN 1000
/*
  还有个处理方式是非本地跳转
*/

FILE *goal_steam;

void handler(int s)
{
  fflush(goal_steam);
  fclose(goal_steam);
}

char *tfgets(char *__restrict __s, int __n, FILE *__restrict __stream)
{
  goal_steam = __stream;
  Signal(SIGALRM, handler);
  Alarm(5);
  char *r = fgets(__s, __n, __stream);
  goal_steam = NULL;
  Signal(SIGALRM, SIG_DFL);
  return r;
}

int main()
{
  char input[LEN] = "";
  if (tfgets(input, LEN, stdin) != NULL)
  {
    printf("tfgets %s", input);
  }
  else
  {
    printf("NULL\n");
  }
  exit(0);
}