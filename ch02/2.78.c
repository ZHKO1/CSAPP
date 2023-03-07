#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int divide_power2(int x, int k)
{
  unsigned w = sizeof(int) << 3;
  int mask = -1 << (w - 1);
  int sign = !!(x & mask);
  return (x + (sign << k) - sign) >> k;
}

int main(int argc, char *argv[])
{
  int x = 12340;
  assert(divide_power2(x, 0) == 12340);
  assert(divide_power2(x, 1) == 6170);
  assert(divide_power2(x, 4) == 771);
  assert(divide_power2(x, 8) == 48);

  x = -12340;
  assert(divide_power2(x, 0) == -12340);
  assert(divide_power2(x, 1) == -6170);
  assert(divide_power2(x, 4) == -771);
  assert(divide_power2(x, 8) == -48);

  x= 0x80000007;
  assert(divide_power2(x, 1) == x / 2);
  assert(divide_power2(x, 2) == x / 4);
  return 0;
}