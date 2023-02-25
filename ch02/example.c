#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
  size_t i;
  for (i = 0; i < len; i++)
  {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_int(int x)
{
  show_bytes((byte_pointer)&x, sizeof(int));
};

void show_float(float x)
{
  show_bytes((byte_pointer)&x, sizeof(float));
};

void show_pointer(void *x)
{
  show_bytes((byte_pointer)&x, sizeof(void *));
};

void test_show_bytes(int val)
{
  int ival = val;
  float fval = (float)ival;
  int *pval = &ival;
  show_int(ival);
  show_float(ival);
  show_pointer(pval);
}

int main()
{
  // P31
  // 显示类型为int，float 和 void * 的C程序对象的字节表示
  {
    test_show_bytes(12345);
    // macbook intel的输出
    // 39 30 00 00
    // 00 e4 40 46
    // 28 95 be e9 fe 7f 00 00
  }

  return 0;
}

