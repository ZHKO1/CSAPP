int printf(const char *format, ...);

int global_init_var = 0x12;
int global_uninit_var;

void func1(int i)
{
  printf("fun func1 printf %d\n", i);
}

int main(void)
{
  static int static_var = 0x35;
  static int static_var2;
  int a = 1;
  int b;
  func1(static_var + static_var2 + a + b);
  return a;
}