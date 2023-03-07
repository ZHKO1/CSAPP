#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void copy_int(int val, void *buf, int maxbytes)
{
  if (maxbytes - sizeof(val) >= 0)
  {
    memcpy(buf, (void *)&val, sizeof(val));
  }
}

void copy_int_1(int val, void *buf, int maxbytes)
{
  if (maxbytes >= (int)sizeof(val))
  {
    memcpy(buf, (void *)&val, sizeof(val));
  }
}

int main()
{
  // A. 当int类型和size_t类型运算时，int会转化为无符号类型，导致怎么计算都是大于等于0的
  // B. 参考copy_int_1
  int maxbytes = sizeof(int) * 10;
  void *buf = malloc(maxbytes);
  int val;

  val = 0x12345678;
  copy_int_1(val, buf, maxbytes);
  assert(*(int *)buf == val);

  val = 0xAABBCCDD;
  buf = malloc(maxbytes);
  copy_int_1(val, buf, 0);
  assert(*(int *)buf != val);

  val = 0x12345678;
  buf = malloc(maxbytes);
  copy_int_1(val, buf, 0xFFFFFFFF);
  assert(*(int *)buf != val);

  free(buf);
  return 0;
}
