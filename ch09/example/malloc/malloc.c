#include <stdio.h>
#include <string.h>
#include "./memlib.h"
#include "./mm.h"
int main(int argc, char *argv[], char *envp[])
{
  mem_init();
  mm_int();
  mm_log();
  char *ptr = (char *)mm_malloc(sizeof(char) * 8);
  strcpy(ptr, "1234567");
  mm_log();
  char *ptr1 = (char *)mm_malloc(sizeof(char) * 12);
  strcpy(ptr1, "abcd");
  mm_log();
  char *ptr2 = (char *)mm_malloc(sizeof(char) * 16);
  strcpy(ptr2, "123456789012345");
  mm_log();
  mm_free(ptr1);
  mm_log();
  char *ptr3 = (char *)mm_malloc(sizeof(char) * 2);
  strcpy(ptr3, "-");
  mm_log();
  mem_free();
  return 0;
}