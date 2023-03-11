
#include "float_bits.h"

int float_f2i(float_bits f)
{
  if (is_float_bits_nan(f))
  {
    return 0x80000000;
  }

  if (is_float_bits_infinity(f))
  {
    return 0x80000000;
  }

  unsigned sign = get_float_bits_sign(f);
  unsigned exp = get_float_bits_exp(f);
  unsigned frac = get_float_bits_frac(f);

  if (exp == 0)
  {
    // 非规格化
    return 0x0;
  }
  else
  {
    // 规格化
    int e = exp - float_bits_biase;
    if (e < 0)
    {
      // E = 1 - Biase
      // 必然小于0
      return 0;
    }
    else if (e >= 31)
    {
      // E > 31
      // 必然大于|Tmin|
      // E == 31
      // 此时也有对应的int类型，正是Tmin
      return 0x80000000;
    }
    else
    {
      if (e <= 23)
      {
        unsigned m = (frac | (1 << 23)) >> (23 - e);
        return sign ? -m : m;
      }
      else
      {
        unsigned m = (frac | (1 << 23)) << (e - 23);
        return sign ? -m : m;
      }
    }
  }
  return f;
}
