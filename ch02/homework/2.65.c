#include <stdio.h>
#include <assert.h>

// 如果有奇数个1则返回1
int odd_ones(unsigned x)
{
  unsigned u16_1 = x & 0xFFFF;
  unsigned u16_2 = x >> 16;
  unsigned u16 = u16_1 ^ u16_2;
  unsigned u8_1 = u16 & 0xFF;
  unsigned u8_2 = u16 >> 8;
  unsigned u8 = u8_1 ^ u8_2;
  unsigned u4_1 = u8 & 0xF;
  unsigned u4_2 = u8 >> 4;
  unsigned u4 = u4_1 ^ u4_2;
  unsigned u2_1 = u8 & 0x3;
  unsigned u2_2 = u8 >> 2;
  unsigned u2 = u2_1 ^ u2_2;
  unsigned u1_1 = u2 & 0x1;
  unsigned u1_2 = u2 >> 1;
  return !!(u1_1 ^ u1_2);

  // 思路是对的，但是还是超过12个算数运算
  // 实际上
  // unsigned u16_1 = x & 0xFFFF;
  // unsigned u16_2 = x >> 16;
  // unsigned u16 = u16_1 ^ u16_2;
  // 可以压缩成
  // x ^= x >> 16;
  // 虽然上一行执行后x的前16位变成1了，但后面16位确实是跟u16统一
  // 总之到最后只需要检查最后一位就行，不需要管剩余31位
}

int main()
{
  assert(odd_ones(0x1) == 1);
  assert(odd_ones(0x3) == 0);
  assert(odd_ones(-1) == 0);
  assert(odd_ones(0xFFF1) == 1);
  assert(odd_ones(0x10101011));
  assert(!odd_ones(0x01010101));
  return 0;
}
