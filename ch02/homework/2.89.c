#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

int B(int x, double dx, int y, double dy)
{
  return dx - dy == (double)(x - y);
}

int C(double dx, double dy, double dz)
{
  return (dx + dy) + dz == dx + (dy + dz);
}

int D(double dx, double dy, double dz)
{
  return (dx * dy) * dz == dx * (dy * dz);
}

int E(double dx, double dz)
{
  return dx / dx == dz / dz;
}

int main(int argc, char *argv[])
{
  /*
  这里需要注意题意，dx,dy,dz都是由int类型对应转化而来

  A. 是
  B. 非 dx - INT_MIN  != (double)(x - INT_MIN)
  C. 是
  D. 非
    参见 https://github.com/DreamAndDead/CSAPP-3e-Solutions/issues/23
    可知，-2^31 <= x,y,z < 2^31，-2^62 <= x*y < 2^62, -2^93 < x*y*z < 2^93,
    而 double 类型，只可以精确地表示 [-2^53-1, 2^53+1] 中的整数。
  E. 非 当dx是1，dz是0
  */
  double dzero = 0;
  printf("dzero / dzero: %lf\n", dzero / dzero);
  // 返回的是-nan
  return 0;
}