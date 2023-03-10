#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  /*
  最小的正非规格化数
  0 0..00 0 0..01
  十进制 2^(-61-2^14)
  最小的正规格化数
  0 0..01 1 0..0
  十进制 2^(2-2^14)
  最大的规格化数
  0 1..10 1 1..1
  (1 - 2^(-n-1))*2^(2^(k-1))
  */
  return 0;
}