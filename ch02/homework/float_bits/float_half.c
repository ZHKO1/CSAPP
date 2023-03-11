
#include "float_bits.h"

float_bits float_half(float_bits f)
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
    frac = get_float_bits_frac_rounding_even(frac, 1);
    return get_float_bits(sign, exp, frac);
  }
  else
  {
    // 规格化
    if (exp == 1)
    {
      // 规格化 转变为 非规格化
      exp = 0;
      frac = get_float_bits_frac_rounding_even(frac, 1);
      frac |= (1 << 22);
      return get_float_bits(sign, exp, frac);
    }
    else
    {
      exp -= 1;
      return get_float_bits(sign, exp, frac);
    }
  }
  return f;
}
