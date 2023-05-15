#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Length 100

void psum1(float a[], float p[], long n)
{
  long i;
  p[0] = a[0];
  for (i = 1; i < n; i++)
  {
    p[i] = p[i - 1] + a[i];
  }
}

void psum3(float a[], float p[], long n)
{
  long i;
  float pre = p[0] = a[0];
  for (i = 1; i < n; i++)
  {
    float now = pre + a[i];
    p[i] = now;
    pre = now;
  }
}

void psum4(float a[], float p[], long n)
{
  long i;
  long k = 6;
  long limit = n - k + 1;
  float pre = 0;
  for (i = 0; i < limit; i += k)
  {
    float a0 = a[i];
    float a1 = a[i + 1];
    float a2 = a[i + 2];
    float a3 = a[i + 3];
    float a4 = a[i + 4];
    float a5 = a[i + 5];
    p[i] = pre + a0;
    p[i + 1] = pre + a0 + a1;
    p[i + 2] = pre + a0 + a1 + a2;
    p[i + 3] = pre + a0 + a1 + a2 + a3;
    p[i + 4] = pre + a0 + a1 + a2 + a3 + a4;
    p[i + 5] = pre = pre + (a0 + a1 + a2 + a3 + a4 + a5);
  }
  for (; i < n; i++)
  {
    float now = pre + a[i];
    p[i] = now;
    pre = now;
  }
}

int main(int argc, char *argv[])
{
  float a[Length] = {};
  for (int i = 0; i < Length; i++)
  {
    a[i] = i + 1;
  }

  float p[Length] = {};
  for (int i = 0; i < Length; i++)
  {
    p[i] = i + 1;
  }
  float p1[Length] = {};
  for (int i = 0; i < Length; i++)
  {
    p1[i] = i + 1;
  }
  float p2[Length] = {};
  for (int i = 0; i < Length; i++)
  {
    p2[i] = i + 1;
  }

  psum1(a, p, Length);
  psum3(a, p1, Length);
  psum4(a, p2, Length);
  printf("%f\n", p[Length - 1]);
  printf("%f\n", p1[Length - 1]);
  printf("%f\n", p2[Length - 1]);
  assert(memcmp(p, p1, Length * sizeof(float)) == 0);
  assert(memcmp(p, p2, Length * sizeof(float)) == 0);
  return 0;
}