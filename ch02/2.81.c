#include <stdio.h>
#include <assert.h>
#include <limits.h>

unsigned A(unsigned k)
{
  return (unsigned)-1 << k;
}

unsigned B(unsigned k, unsigned j)
{
  int right = A(j);
  int left = ~A(k + j);
  return left & right;
}

int main(int argc, char *argv[])
{
  assert(A(8) == 0xFFFFFF00);
  assert(B(16, 8) == 0x00FFFF00);
  return 0;
}