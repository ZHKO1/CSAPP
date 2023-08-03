#include <stdio.h>
#include <string.h>
#include "./memlib.h"
#include "./mm.h"
int main(int argc, char *argv[], char *envp[])
{
  printf("--- 执行mem_init 和 mm_int\n");
  mem_init();
  mm_int();
  mm_log();
  printf("\n");

  printf("--- 分配8个字节 内部放了字符串1234567\n");
  char *ptr = (char *)mm_malloc(sizeof(char) * 8);
  strcpy(ptr, "1234567");
  printf("strcpy完毕\n");
  mm_log();
  printf("\n");

  printf("--- 分配12个字节 内部放了字符串abcd\n");
  char *ptr1 = (char *)mm_malloc(sizeof(char) * 12);
  strcpy(ptr1, "abcd");
  mm_log();
  printf("\n");

  printf("--- 分配16个字节 内部放了字符串123456789012345\n");
  char *ptr2 = (char *)mm_malloc(sizeof(char) * 16);
  strcpy(ptr2, "123456789012345");
  mm_log();
  printf("\n");

  printf("--- 将12个字节的空间执行free\n");
  mm_free(ptr1);
  mm_log();
  printf("\n");

  printf("--- 分配2个字节 内部放了字符串-\n");
  char *ptr3 = (char *)mm_malloc(sizeof(char) * 2);
  strcpy(ptr3, "-");
  mm_log();
  printf("\n");

  mem_free();
  return 0;
}