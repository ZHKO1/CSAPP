#include <stdio.h>
#include <assert.h>

unsigned rotate_left(unsigned x, int n)
{
  unsigned w = sizeof(int) << 3;
  unsigned left = x >> (w - n);
  unsigned right = x << n;
  return left | right;
}

int main()
{
  assert(rotate_left(0x12345678, 4) == 0x23456781);
  assert(rotate_left(0x12345678, 20) == 0x67812345);
  assert(rotate_left(0x12345678, 0) == 0x12345678);
  return 0;
}
