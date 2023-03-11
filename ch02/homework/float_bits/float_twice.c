
#include "float_bits.h"

float_bits float_twice(float_bits f)
{
  if (is_float_bits_nan(f))
  {
    return f;
  }

  if (is_float_bits_infinity(f))
  {
    return f;
  }

  unsigned sign = get_float_bits_sign(f);
  unsigned exp = get_float_bits_exp(f);
  unsigned frac = get_float_bits_frac(f);

  if (exp == 0)
  {
    // 非规格化
    unsigned frac_high_bit = frac >> 22;
    if (!frac_high_bit)
    {
      // frac左移即可
      frac = (frac << 1) & 0x7FFFFF;
      return get_float_bits(sign, exp, frac);
    }
    else
    {
      // 非规格 变化为 规格化
      frac = (frac << 1) & 0x7FFFFF;
      exp = 1;
      return get_float_bits(sign, exp, frac);
    }
  }
  else
  {
    // 规格化
    int e = exp - float_bits_biase + 1;
    if (e <= float_bits_maxE)
    {
      exp += 1;
      return get_float_bits(sign, exp, frac);
    }
    else
    {
      exp = 0xFF;
      frac = 0;
      return get_float_bits(sign, exp, frac);
    }
  }
  return f;
}