#include <stdio.h>
#include <assert.h>

unsigned srl(unsigned x, int k)
{
  unsigned xsra = (int)x >> k;
  unsigned w = sizeof(int) << 3;
  unsigned mask;
  mask = (1 << (w - k)) - 1;
  // 也可以 mask = (unsigned) -1 >> k;
  return xsra & mask;
}

int sra(int x, int k)
{
  // 这里的难点是符号整数有两种可能，正数或负数
  // 那么要怎么同时兼顾到这两种情况是关键
  int xsrl = (unsigned)x >> k;
  unsigned w = sizeof(int) << 3;
  int is_negative = (x & (1 << (w - 1))) == (1 << (w - 1));
  unsigned mask;
  mask = ~((is_negative << (w - k)) - 1);
  return xsrl | mask;
}

int sra1(int x, int k)
{
  // 更优雅的解法
  int xsrl = (unsigned)x >> k;
  unsigned w = sizeof(int) << 3;
  unsigned mask = ~((unsigned)-1 >> k);
  // 判断x是否正数
  unsigned leftest_bit = 1 << (w - 1);
  unsigned is_pos = !(x & leftest_bit);
  // 画龙点睛之笔，如果is_pos是1，那么mask被清0，如果is_pos是负，那么mask&-1，相当于mask没变
  mask = mask & (is_pos - 1); 
  return xsrl | mask;
}

int main()
{
  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);
  assert(sra1(test_int, 4) == test_int >> 4);

  test_unsigned = 0x87654321;
  test_int = 0x87654321;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);
  assert(sra1(test_int, 4) == test_int >> 4);

  return 0;
}
