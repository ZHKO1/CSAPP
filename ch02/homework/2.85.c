#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  /*
  k位指数 n位小数
  阶码E 尾数M 小数f 值V
  A. 数7.0
  阶码E 2
  尾数M 1.11
  小数f 0.11
  V 1.11 * 2^2
  B. 能够被准确描述的最大奇整数
  阶码E n
  尾数M 1.11111 小数位有n个
  小数f 0.11111 小数位有n个
  V 1.11111 * 2^n
  C. 最小的规格化数的倒数
  阶码E 2^(k - 1)-2
  尾数M 1.00
  小数f 0.00
  V 1.00 * 2^(2^(k - 1)-2)
  */
  return 0;
}