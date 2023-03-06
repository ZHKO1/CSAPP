#include <stdio.h>
#include <assert.h>

/*
int bad_int_size_is_32()
{
  int set_msb = 1 << 31;
  int beyond_msb = 1 << 32;
  return set_msb && !beyond_msb;
}
*/

int int_size_is_32()
{
  int set_msb = 1 << 31;
  int beyond_msb = set_msb << 1;
  return set_msb && (beyond_msb == 0);
}

int int_size_is_32_other()
{
  int set_msb = 1 << 15;
  set_msb = set_msb << 15;
  set_msb = set_msb << 1;
  int beyond_msb = set_msb << 1;
  return set_msb && (beyond_msb == 0);
}

int main()
{
  // A. 左移位超过31
  // B. 参考int_size_is_32
  // C. 参考int_size_is_32_other
  assert(int_size_is_32());
  assert(int_size_is_32_other());
  return 0;
}
