#include <stdio.h>
#include <assert.h>

// x能不能用n位补码来表示
int fits_bits(int x, int n)
{
  unsigned w = sizeof(int) << 3;
  unsigned offset = (w - n);
  return (x << offset) >> offset == x;
}

int main()
{
  assert(!fits_bits(0xFF, 8));
  assert(!fits_bits(~0xFF, 8));

  assert(fits_bits(0b0010, 3));
  assert(!fits_bits(0b1010, 3));
  assert(!fits_bits(0b0110, 3));

  assert(fits_bits(~0b11, 3));
  assert(!fits_bits(~0b01000011, 3));
  assert(!fits_bits(~0b111, 3));
  return 0;
}
