#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  /*
  -0
  Hex 0x8000
  M 0
  E -14
  V -0
  D -0.0

  最小的>2的值
  Hex 0x4001
  M 1.0..01
  E 1=16-15
  V 1025/1024*2
  D 2.001953

  512
  Hex 0x6000
  M 1.0..00
  E 9=24-15
  V 512
  D 512

  最大的非规格化数
  Hex 0x03FF
  M 0.1...1
  E -14=1-15
  V (1023/1024)*2^(-14)
  D 0.000244

  负无限
  Hex 0xFC00

  0x3BB0
  Hex 0x3BB0
  M 1.1110110000
  E -1=14-15
  V 123/128
  D 0.960938
  */
  return 0;
}