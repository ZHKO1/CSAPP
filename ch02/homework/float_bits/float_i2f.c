
#include "float_bits.h"
#include <assert.h>

unsigned get_leftest_one_index(unsigned x)
{
  assert(x != 0);
  unsigned index = 0;
  while ((x = x >> 1))
  {
    index += 1;
  }
  return index;
}

float_bits float_i2f(int i)
{
  if (i == 0x0)
  {
    unsigned sign = 0;
    unsigned exp = 0;
    unsigned frac = 0;
    return get_float_bits(sign, exp, frac);
  }

  if (i == 0x80000000)
  {
    unsigned sign = 1;
    unsigned exp = 31 + float_bits_biase;
    unsigned frac = 0;
    return get_float_bits(sign, exp, frac);
  }

  unsigned sign = (i < 0);
  unsigned abs_num = i;
  if (sign)
  {
    abs_num = -i;
  }

  unsigned leftest_one_index = get_leftest_one_index(abs_num);
  unsigned exp = leftest_one_index + float_bits_biase;
  // printf("leftest_one_index: %u\n", leftest_one_index);
  // printf("exp:%x\n", exp);
  unsigned frac_M = 0;
  // 规格化数的尾数M是1 + 0.fffff(ffff对应frac)
  if (leftest_one_index <= 23)
  {
    frac_M = abs_num << (23 - leftest_one_index);
  }
  else
  {
    frac_M = get_float_bits_frac_rounding_even(abs_num, leftest_one_index - 23);
    // 再次检查偶数舍入是否让最左侧的1也进位了
    unsigned frac_M_integer = frac_M >> 23;
    if (frac_M_integer > 1)
    {
      exp += 1;
    }
  }
  return get_float_bits(sign, exp, frac_M & 0x7FFFFF);
}
