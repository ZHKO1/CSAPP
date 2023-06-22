#include "../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
  int i = 0;
  printf("Command-ine arguments\n");
  for (i = 0; i < argc; i++)
  {
    printf("arg[%d]: %s\n", i, argv[i]);
  }
  printf("Environment variables\n");
  i = 0;
  char *env = NULL;
  while (env = envp[i++])
  {
    printf("envp[%d]: %s\n", i, env);
  };
  return 0;
}