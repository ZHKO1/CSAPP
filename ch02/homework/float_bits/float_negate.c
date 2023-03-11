
#include "float_bits.h"

float_bits float_negate(float_bits f)
{
  int is_nan = is_float_bits_nan(f);
  if (is_nan)
  {
    return f;
  }
  unsigned sign = get_float_bits_sign(f);
  unsigned exp = get_float_bits_exp(f);
  unsigned frac = get_float_bits_frac(f);
  sign = !sign;
  return get_float_bits(sign, exp, frac);
}