#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void *calloc1(size_t nmemb, size_t size)
{
  if (nmemb == 0 || size == 0)
  {
    return NULL;
  }
  size_t all_size = nmemb * size;
  if (nmemb == all_size / size)
  {
    void *p = malloc(all_size);
    if (p != NULL)
    {
      memset(p, 0, all_size);
    }
    return p;
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  void *p;
  p = calloc1(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = calloc1(SIZE_MAX, 2);
  assert(p == NULL);
  free(p);
  return 0;
}