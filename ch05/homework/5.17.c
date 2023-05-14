#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void *basic_memset(void *s, int c, size_t n)
{
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n)
  {
    *schar++ = (unsigned char)c;
    cnt++;
  }
  return s;
}

void *effective_memset(void *s, int c, size_t n)
{
  unsigned char unit = (unsigned char)c;
  unsigned long k = sizeof(unsigned long);
  unsigned long long_unit = 0;
  for (int i = 0; i < k; i++)
  {
    long_unit = long_unit | (unit << i * 8);
  }
  long limit = n - k + 1;
  long i;
  unsigned long *slong = s;
  for (i = 0; i < limit; i += k)
  {
    *slong++ = long_unit;
  }
  unsigned char *schar = (unsigned char *)slong;
  for (; i < n; i++)
  {
    *schar++ = unit;
  }
  return s;
}

int main(int argc, char *argv[])
{
  size_t space = sizeof(char) * 65537;
  // careful! malloc SIZE_MAX size memory will make sys slow
  // or crash down
  // size_t space = SIZE_MAX;

  void *basic_space = malloc(space);
  void *effective_space = malloc(space);

  int basic_fill = 0xFF;
  unsigned long effective_fill = ~0;

  basic_memset(basic_space, basic_fill, space);
  effective_memset(effective_space, basic_fill, space);

  assert(memcmp(basic_space, effective_space, space) == 0);

  free(basic_space);
  free(effective_space);
  return 0;
}