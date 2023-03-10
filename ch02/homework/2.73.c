#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 正溢出，饱和加法返回TMax，负溢出时，返回TMin
int saturating_add(int x, int y)
{
  int result = x + y;
  unsigned w = sizeof(int) << 3;
  unsigned mask = 1 << (w - 1);
  unsigned x_sign = !!(x & mask);
  unsigned y_sign = !!(y & mask);
  unsigned pos_over = !y_sign && !x_sign && !!((x + y) & mask);
  unsigned neg_over = y_sign && x_sign && !((x + y) & mask);

  pos_over && (result = INT_MAX);
  neg_over && (result = INT_MIN);

  return result;
}

int main()
{
  assert(saturating_add(1, 2) == 3);
  assert(saturating_add(INT_MAX, 1) == INT_MAX);
  assert(saturating_add(INT_MIN, -1) == INT_MIN);

  assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
  assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
  assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
  return 0;
}
