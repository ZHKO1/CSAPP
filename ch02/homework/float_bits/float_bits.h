
#define float_bits_biase (127)
#define float_bits_maxE (127)

typedef unsigned float_bits;

unsigned get_float_bits_sign(float_bits x);
unsigned get_float_bits_exp(float_bits x);
unsigned get_float_bits_frac(float_bits x);
unsigned get_float_bits_frac_rounding_even(unsigned frac, unsigned offset);
unsigned get_float_bits(unsigned sign, unsigned exp, unsigned frac);
int is_float_bits_nan(float_bits x);
int is_float_bits_infinity(float_bits x);