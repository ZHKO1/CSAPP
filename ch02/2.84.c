#include <stdio.h>
#include <assert.h>
#include <limits.h>

float u2f(unsigned x)
{
  return *(float *)&x;
}

unsigned f2u(float x)
{
  // 学到了一个小技巧，还能这样同位转化
  return *(unsigned *)&x;
}

int float_le(float x, float y)
{
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;
  // printf("%f %f\n", x, y);
  // printf("%x %x\n", ux, uy);
  return (((ux << 1) == 0) && ((uy << 1) == 0)) ||
      (!sx && !sy && ux <= uy) ||
      (sx && sy && ux >= uy) ||
      (sx && !sy);
}

int main(int argc, char *argv[])
{
  // 需要注意+0和-0
  float zero_pos = u2f(0);
  float zero_neg = u2f(1<<31);
  assert(float_le(zero_neg, zero_pos));
  assert(float_le(zero_pos, zero_neg));
  // 如下两行的-0不清楚为什么float类型的sign位依然还是0,因此测不出+0和-0的问题...
  assert(float_le(-0, +0));
  assert(float_le(+0, -0));
  assert(float_le(0, 3));
  assert(float_le(-4, -0));
  assert(float_le(-4, 4));
  return 0;
}