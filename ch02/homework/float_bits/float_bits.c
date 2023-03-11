#include <math.h>
#include "float_bits.h"

unsigned get_float_bits_sign(float_bits x)
{
  return x >> 31;
}

unsigned get_float_bits_exp(float_bits x)
{
  return x >> 23 & 0xFF;
}

unsigned get_float_bits_frac(float_bits x)
{
  return x & 0x7FFFFF;
}

// 偶数舍入
unsigned get_float_bits_frac_rounding_even(unsigned frac, unsigned offset)
{
  if (offset == 0)
  {
    return frac;
  }
  // 中间值
  unsigned middle_value = (frac & (-1 << offset)) | (1 << (offset - 1));
  if (frac < middle_value)
  {
    // 小于中间值 则舍
    return (frac >> offset);
  }
  else if (frac > middle_value)
  {
    // 大于中间值 则进
    return (frac >> offset) + 1;
  }
  else
  {
    unsigned guard_bit = (frac >> offset) & 0x1;
    // 保留位 偶舍 奇进
    if (guard_bit % 2 == 0)
    {
      return (frac >> offset);
    }
    else
    {
      return (frac >> offset) + 1;
    }
  }
}

unsigned get_float_bits(unsigned sign, unsigned exp, unsigned frac)
{
  return (sign << 31) | (exp << 23) | (frac & 0x7FFFFF);
}

int is_float_bits_nan(float_bits x)
{
  unsigned exp = get_float_bits_exp(x);
  unsigned frac = get_float_bits_frac(x);
  return (exp == 0xFF) && (frac != 0);
}

int is_float_bits_infinity(float_bits x)
{
  unsigned exp = get_float_bits_exp(x);
  unsigned frac = get_float_bits_frac(x);
  return (exp == 0xFF) && (frac == 0);
}
