#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "lib/random.h"
#include "float_bits.h"
#include "float_negate.h"
#include "float_absval.h"
#include "float_twice.h"
#include "float_half.h"
#include "float_f2i.h"
#include "float_i2f.h"

unsigned f2u(float f)
{
  return *(unsigned *)&f;
}

float u2f(unsigned u)
{
  return *(float *)&u;
}

void test_case(unsigned r)
{
  /*r = n;*/
  printf("r:\t0x%.8X\t%d\n", r, r);

  float f = u2f(r);
  printf("f:\t0x%.8X\t%.50f\n", f2u(f), f);

  float fmul2 = f * 2.0;
  printf("fmul2:\t0x%.8X\t%.50f\n", f2u(fmul2), fmul2);

  float fdiv2 = f * 0.5;
  printf("fdiv2:\t0x%.8X\t%.50f\n", f2u(fdiv2), fdiv2);

  int f2i = (int)f;
  printf("f2i:\t0x%.8X\t%d\n", f2i, f2i);

  float i2f = (float)(int)r;
  printf("r:\t0x%.8X\t%d\n", r, r);
  printf("i2f:\t0x%.8X\t%.50f\n", f2u(i2f), i2f);

  if (isnan(f))
  {
    assert(float_negate(r) == r);
    assert(float_absval(r) == r);
    assert(float_twice(r) == r);
    assert(float_half(r) == r);
    assert(float_f2i(r) == f2i);
  }
  else
  {
    assert(u2f(float_negate(r)) == -f);
    assert(u2f(float_absval(r)) == fabsf(f));
    assert(u2f(float_twice(r)) == fmul2);
    assert(u2f(float_half(r)) == fdiv2);
    /* whether f > (float)INT_MAX || f < (float)INT_MIN) */
    assert(float_f2i(r) == f2i);
  }
  float my_i2f = u2f(float_i2f(r));
  printf("my_i2f:\t0x%.8X\t%.50f\n", f2u(my_i2f), my_i2f);
  assert(my_i2f == i2f);

  printf("\n");
}

int main(int argc, char *argv[])
{
  unsigned cases[30] = {
      0b00000000000000000000000000000000, // 0
      0b00000000000000000000000000000001, // 最小非规格化
      0b00000000000001001110000000010101,
      0b00000000000001001110000000010110,
      0b00000000000001001110000000010011,
      0b00000000011111111111111111111111, // 最大非规格化
      0b00000000100000000000000000000000, // 最小规格化
      0b00000000100000111110011110000110,
      0b00001111100000111110011110000101,
      0b01000111100000111110011110000011,
      0b01111111100000000000000000000000, // 1
      0b01111111011111111111111111111111, // 最大规格化数
      0b01111111100000000000000000000000, // 正无穷大
      0b01111111111111111111111111111110, // NAN
      0b01111111111111111111111111111111, // NAN

      // 负符号位
      0b10000000000000000000000000000000, // 0
      0b10000000000000000000000000000001, // 最小非规格化
      0b10000000000001001110000000010101,
      0b10000000000001001110000000010110,
      0b10000000000001001110000000010011,
      0b10000000011111111111111111111111, // 最大非规格化
      0b10000000100000000000000000000000, // 最小规格化
      0b10000000100000111110011110000110,
      0b10001111100000111110011110000101,
      0b11000111100000111110011110000011,
      0b11111111100000000000000000000000, // 1
      0b11111111011111111111111111111111, // 最大规格化数
      0b11111111100000000000000000000000, // 无穷大
      0b11111111111111111111111111111110, // NAN
      0b11111111111111111111111111111111, // NAN
  };

  for (unsigned index = 0; index < 30; index = index + 1)
  {
    unsigned r = cases[index];
    test_case(r);
  }

  for (unsigned n = 0, round = 0; !round; n = n + 1)
  {
    if (n == 0xFFF)
    {
      round++;
    }

    // test all int numbers waste a lot of time
    // just test 0xFFF random numbers here
    unsigned r = random_int();
    test_case(r);
  }
}