#include "../lib/csapp.h"
#include <stdlib.h>
/*
  这道题很奇怪
  bash 不支持 setenv
  c语言调用setenv，也没看到命令行宽度有变化
  甚至调用getenv，只能拿到NULL
*/
int main(int argc, char *argv[], char *envp[])
{
  char filename[100] = "/bin/ls";
  char env_key[100] = "COLUMNS";
  char *env_value_origin = getenv(env_key);
  if (env_value_origin == NULL)
  {
    printf("env %s = NULL\n", env_key);
  }
  else
  {
    printf("env %s = %s\n", env_key, env_value_origin);
  }

  if (execve(filename, argv, envp) < 0)
  {
    printf("execve %s error\n", argv[0]);
    exit(1);
  }

  return 0;
}