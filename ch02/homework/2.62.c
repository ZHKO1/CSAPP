#include <stdio.h>
#include <assert.h>

// 对int类型的数使用算数右移的机器上运行时，函数生成1，其他情况生成0
int int_shifts_are_arithmetic()
{
  unsigned shift = sizeof(int) << 3;
  int i = -1;
  return (i >> 1) == -1;
}

int main()
{
  assert(int_shifts_are_arithmetic() == 1);
  return 0;
}
