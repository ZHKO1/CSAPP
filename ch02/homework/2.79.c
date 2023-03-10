#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 这里题目的意思是可以允许3*x产生溢出
// 说人话就是先乘3，在除以4
int mul3div4(int x)
{
  int xmul3 = (x << 1) + x;
  unsigned w = sizeof(int) << 3;
  int mask = -1 << (w - 1);
  int sign = !!(x & mask);
  int biase = 0;
  int k = 2;
  sign && (biase = ((1 << k) - 1));
  return (xmul3 + biase) >> k;
}

int main(int argc, char *argv[])
{
  int x = 0x87654321;
  assert(mul3div4(x) == x * 3 / 4);
  return 0;
}