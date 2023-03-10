#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <inttypes.h>

int signed_high_prod(int x, int y)
{
  int64_t result = (int64_t)x * (int64_t)y;
  return result >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
  /*
  x'y'是无符号乘积
  xy 是有符号乘积
  x' = x + x31*2^32
  y' = y + y31*2^32
  x'y' = xy + x*y31*2^32 + y*x31*2^32 + x31y31*2^64
  因为完整的位长是2w，也就是64位，所以超过64位长的需要被舍去
  x'y'mod64 = xy + x*y31*2^32 + y*x31*2^32
  这里题目需要求高w位，所以我们还需要>>32
  x'y'mod64 >> 32 = xy >> 32 + x*y31 + y*x31
  */
  unsigned x_31 = x >> 31;
  unsigned y_31 = y >> 31;
  int signed_high_prod_result = signed_high_prod(x, y);
  return signed_high_prod_result + (int)x * (int)y_31 + (int)y * (int)x_31;
}

unsigned another_unsigned_high_prod(unsigned x, unsigned y)
{
  uint64_t mul = (uint64_t)x * y;
  return mul >> 32;
}

int main(int argc, char *argv[])
{
  unsigned x = 0x12345678;
  unsigned y = 0xFFFFFFFF;
  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));

  x = 0x82345678;
  y = 0xFFFFFFFF;
  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));

  x = 0x82345678;
  y = 0x82345678;
  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));

  return 0;
}