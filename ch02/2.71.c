#include <stdio.h>
#include <assert.h>

typedef unsigned packet_t;

int xbyte(packet_t word, int bytenum)
{
  int x = (int)word;
  int right_offset = 24;
  int left_offset = (3 - bytenum) << 3;
  return x << left_offset >> 24;
}

int main()
{
  // A. 错在无法提取出负数
  assert(xbyte(0x12345678, 0) == 0x78);
  assert(xbyte(0x12345678, 1) == 0x56);
  assert(xbyte(0x12345678, 2) == 0x34);
  assert(xbyte(0x12345678, 3) == 0x12);
  assert(xbyte(0x87654321, 0) == 0x21);
  assert(xbyte(0x87654321, 1) == 0x43);
  assert(xbyte(0x87654321, 2) == 0x65);
  assert(xbyte(0x87654321, 3) == 0xFFFFFF87);

  assert(xbyte(0x00112233, 0) == 0x33);
  assert(xbyte(0x00112233, 1) == 0x22);
  assert(xbyte(0x00112233, 2) == 0x11);
  assert(xbyte(0x00112233, 3) == 0x00);

  assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
  assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
  assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
  assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);
  return 0;
}
