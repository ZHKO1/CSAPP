#include "../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
  alarm(20);
  sleep(5);
  unsigned int rc = alarm(5);
  printf("5秒后第一个alarm被取消，新的alarm会返回前一个alarm闹钟剩下的秒数%d\n", rc); 
  sleep(10);
  // 实际上sleep只执行了5秒，因为被第二个alarm信号打断
  return 0;
}