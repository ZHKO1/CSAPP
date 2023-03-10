#include <stdio.h>
#include <assert.h>
#include <limits.h>

int tadd_ok(int x, int y)
{
  int result = x + y;
  int add_1 = (x > 0) && (y > 0) && (result < x);
  int add_2 = (x < 0) && (y < 0) && (result > x);
  return !add_1 && !add_2;
}

// 如果x-y不溢出，则返回1
int tsub_ok(int x, int y)
{
  if (y == INT_MIN)
  {
    // 不能用tadd_ok(x, -y)，由于补码自身机制，-INT_MIN的位表示还是INT_MIN
    // 所以会导致x-y变成x+y，从x+y角度来看是没溢出，但是实际上x-y从数学意义上来讲还是溢出了
    // 当y是INT_MIN时，如果x是非负数，显然x-y是会超过Tmin到Tmax这个范围，也就是溢出了。如果x是负数，则没溢出
    if (x < 0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return tadd_ok(x, -y);
  }
}

int main()
{
  assert(!tsub_ok(0x00, INT_MIN));
  assert(tsub_ok(0x00, 0x00));
  return 0;
}
