#include <stdio.h>
#include <assert.h>
#include <limits.h>

// 这里题目意思是不允许产生溢出
// 说人话就是先除以4，再乘3
// 同时也需要注意向0舍入
int threefourths(int x)
{
  // 我给出的第一个答案是 x - (x >> 2)，因为满足了不溢出的条件
  // 然而实际测试后就知道是错的，比如x=5，按上面计算出的是4，实际答案是3
  // 显然这做法在精度上是有问题的
  // 那么再考虑直接除以4，再乘以3
  // int xdiv4 = divide_power2(x, 2);
  // 然后再执行 xdiv4 << 1 + xdiv4
  // 经测试在x=5情况下，返回3，看起来没毛病，实际上在x=3情况下还是错的
  // 看起来又是精度上出问题了，总结下来如果除法这步骤不放到最后一步，精度就是会出问题
  // 那么有没有除法放到最后一步，还能不溢出的方法呢？
  // 答案就是分成两段
  // 高30位肯定能整除以4，所以可以先计算除法再计算乘法
  // 低2位需要高精度计算，那就先计算乘法再计算除法（同时向0舍入）
  unsigned w = sizeof(int) << 3;
  int mask = -1 << (w - 1);
  int sign = !!(x & mask);
  // int is_neg = x & INT_MIN; 这做法更简单暴力

  int l = x & ~0x3;
  int r = x & 0x3;
  int ldiv4 = l >> 2;
  int ldiv4mul3 = (ldiv4 << 1) + ldiv4;
  int rmul3 = (r << 1) + r;
  int biase = 0;
  int k = 2;
  sign && (biase = ((1 << k) - 1));
  int rmul3div4 = (rmul3 + biase) >> k;
  return ldiv4mul3 + rmul3div4;
}

int main(int argc, char *argv[])
{
  assert(threefourths(8) == 6);
  assert(threefourths(9) == 6);
  assert(threefourths(10) == 7);
  assert(threefourths(11) == 8);
  assert(threefourths(12) == 9);

  assert(threefourths(-8) == -6);
  assert(threefourths(-9) == -6);
  assert(threefourths(-10) == -7);
  assert(threefourths(-11) == -8);
  assert(threefourths(-12) == -9);
  return 0;
}