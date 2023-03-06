#include <stdio.h>
#include <assert.h>

// 如果有任意偶数位为1则返回1
int any_odd_one(unsigned x)
{
  return !!(x & 0xAAAAAAAA);
}

int main()
{
  unsigned x = 0x1;
  assert(any_odd_one(x) == 0);
  x = 0x2;
  assert(any_odd_one(x) == 1);
  x = 0x4;
  assert(any_odd_one(x) == 0);
  return 0;
}
