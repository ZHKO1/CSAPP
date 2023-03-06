#include <stdio.h>
#include <assert.h>
unsigned replace_byte(unsigned x, int i, unsigned char b){
  unsigned shift = (unsigned)i * 8;
  unsigned mask = 0xFF << shift;
  return (b << shift) | (x & ~mask);
}

int main()
{
    assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
    assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);
    return 0;
}
