#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

int main(int argc, char *argv[])
{
  /*
  biase = 2^(k - 1) - 1 = 127
  非规格 1 - biase = -126
  if x < -149
  too small.return 0.0
  exp = 0;
  frac = 0;

  else if x < -126
  denormalized result
  exp = 0;
  frac = 1 << (23 + 126 + x);

  else if x < 128
  denormalized result
  exp = (127 + x);
  frac = 0;

  else
  too big
  exp = 0xFF;
  frac = 0;
  */
  return 0;
}