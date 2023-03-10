#include <stdio.h>
#include <assert.h>

// 不能使用 == 或 !=

// x的任何位都等于1
int A(int x)
{
  return !(x + 1);
}

// x的任何位都等于0
int B(int x)
{
  return !x;
}

// x最低有效字节中的位都等于1
int C(int x)
{
  return !~(x | ~0xFF);
}

// x最高有效字节中的位都等于0
int D(int x)
{
  unsigned ux = (unsigned)x;
  unsigned shift = sizeof(int) << 3;
  return !(ux >> (shift * 8 - 8));
}

int main()
{
  int all_bit_one = ~0;
  int all_bit_zero = 0;

  assert(A(all_bit_one));
  assert(!B(all_bit_one));
  assert(C(all_bit_one));
  assert(!D(all_bit_one));

  assert(!A(all_bit_zero));
  assert(B(all_bit_zero));
  assert(!C(all_bit_zero));
  assert(D(all_bit_zero));

  // test magic number 0x1234ff
  assert(!A(0x1234ff));
  assert(!B(0x1234ff));
  assert(C(0x1234ff));
  assert(D(0x1234ff));

  // test magic number 0x1234
  assert(!A(0x1234));
  assert(!B(0x1234));
  assert(!C(0x1234));
  assert(D(0x1234));
  return 0;
}
