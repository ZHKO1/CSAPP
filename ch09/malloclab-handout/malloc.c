#include <stdio.h>
#include <string.h>
#include "./memlib.h"
#include "./mm.h"

int main(int argc, char *argv[], char *envp[])
{
  printf("--- 执行mem_init 和 mm_int\n");
  mem_init();
  mm_init();
  mm_log();
  printf("\n");

  printf("--- 分配512个字节 memset(ptr, 'a', 512);\n");
  char *ptr = (char *)mm_malloc(sizeof(char) * 512);
  memset(ptr, 'a', 512);
  printf("strcpy完毕\n");
  mm_log();
  printf("\n");

  printf("--- 分配128个字节 memset(ptr1, 'b', 128);\n");
  char *ptr1 = (char *)mm_malloc(sizeof(char) * 128);
  memset(ptr1, 'b', 128);
  mm_log();
  printf("\n");

  printf("--- 将512个字符扩展到640个字节 memset(ptr2, 'c', 640);\n");
  char *ptr2 = (char *)mm_realloc(ptr, sizeof(char) * 640);
  memset(ptr2, 'c', 640);
  mm_log();
  printf("\n");

  printf("--- 分配128个字节 memset(ptr3, 'd', 128);d\n");
  char *ptr3 = (char *)mm_malloc(sizeof(char) * 128);
  memset(ptr3, 'd', 128);
  mm_log();
  printf("\n");

  printf("--- 将第一个128个字节的空间执行free\n");
  mm_free(ptr1);
  mm_log();
  printf("\n");

  printf("--- 将640个字符扩展到768个字节 memset(ptr4, 'e', 768);\n");
  char *ptr4 = (char *)mm_realloc(ptr2, sizeof(char) * 768);
  memset(ptr4, 'e', 768);
  mm_log();
  printf("\n");

  printf("--- 分配128个字节 memset(ptr5, 'f', 128);\n");
  char *ptr5 = (char *)mm_malloc(sizeof(char) * 128);
  memset(ptr5, 'f', 128);
  mm_log();
  printf("\n");

  mem_deinit();
  return 0;
}