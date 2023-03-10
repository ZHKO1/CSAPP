#include <stdio.h>
#include <assert.h>

// 除了最左边的1，其他的1都清0
int leftmost_one(unsigned x)
{
  // 题解非常巧妙，只需要拼凑成提示所说的[0...0011...1]这种格式即可，后续就自然很容易处理
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return (x >> 1) + (x && 1);
}

int main()
{
  assert(leftmost_one(0xFF00) == 0x8000);
  assert(leftmost_one(0x6000) == 0x4000);
  assert(leftmost_one(0x0) == 0x0);
  assert(leftmost_one(0x80000000) == 0x80000000);
  return 0;
}
