#include <stdio.h>
#include <assert.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  /*
  0 10110 101
  M 1 + 5/8
  E 7=22-15
  V (13/8)*2^7
  A：208
  B: 0 1110 1010    208
  
  1 00111 110
  M 1 + 6/8
  E -8=7-15
  V (14/8)*2^-8
  A：-14/2048
  B: 1 0000 0111    -14/2048

  0 00000 101
  M 5/8
  E -14=1-15
  V (5/8)*2^-14
  A：5*2^-11
  B: 0 0000 0001    1*2^-10

  1 11011 000
  M 1
  E 12=27-15
  V (1)*2^12
  A：-2^12
  B: 1 1110 1111  -31*2^3

  0 11000 100
  M 1 + 4/8
  E 9=24-15
  V (12/8)*2^9
  A：12*2^6
  B: 0 1111 0000    正无限

  */
  return 0;
}