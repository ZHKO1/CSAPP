#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int A(int x)
{
  return x + (x << 4);
}

int B(int x)
{
  return x - (x << 3);
}

int C(int x)
{
  return (x << 6) - (x << 2);
}

int D(int x)
{
  return (x << 4) - (x << 7);
}

int main(int argc, char *argv[])
{
  int x = 0x123;
  assert(A(x) == x * 17);
  assert(B(x) == x * -7);
  assert(C(x) == x * 60);
  assert(D(x) == x * -112);

  x = -1;
  assert(A(x) == x * 17);
  assert(B(x) == x * -7);
  assert(C(x) == x * 60);
  assert(D(x) == x * -112);

  return 0;
}