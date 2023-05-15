#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Length 100

double poly(double a[], double x, long degree)
{
  long i;
  double result = a[0];
  double xpwr = x;
  for (i = 1; i <= degree; i++)
  {
    result += a[i] * xpwr;
    xpwr = x * xpwr;
  }
  return result;
}

double poly_(double a[], double x, long degree)
{
  long i;
  long k = 6;
  double result = 0;
  double result1 = 0;
  double result2 = 0;
  double result3 = 0;
  double result4 = 0;
  double result5 = 0;

  long limit = degree - k + 1;

  double xpwr = 1;
  double xpwr1 = x;
  double xpwr2 = x * x;
  double xpwr3 = x * x * x;
  double xpwr4 = x * x * x * x;
  double xpwr5 = x * x * x * x * x;
  double xpwr_step = x * x * x * x * x * x;
  for (i = 0; i <= limit; i += k)
  {
    result += a[i] * xpwr;
    result1 += a[i + 1] * xpwr1;
    result2 += a[i + 2] * xpwr2;
    result3 += a[i + 3] * xpwr3;
    result4 += a[i + 4] * xpwr4;
    result5 += a[i + 5] * xpwr5;

    xpwr *= xpwr_step;
    xpwr1 *= xpwr_step;
    xpwr2 *= xpwr_step;
    xpwr3 *= xpwr_step;
    xpwr4 *= xpwr_step;
    xpwr5 *= xpwr_step;
  }
  for (; i < degree; i++)
  {
    result += a[i] * xpwr;
    xpwr = x * xpwr;
  }
  return result + result1 + result2 + result3 + result4 + result5;
}

int main(int argc, char *argv[])
{
  size_t space = sizeof(char) * 200;

  double a[Length] = {1, 2, 3, 4, 5, 6};
  for (int i = 0; i < Length; i++)
  {
    a[i] = i + 1;
  }

  /*
  for (int i = 0; i < Length; i++)
  {
    printf("%f\n", a[i]);
  }
  printf("%f\n", poly(a, 2, Length));
  printf("%f\n", poly_(a, 2, Length));
  */
  assert(poly(a, 2, Length) == poly_(a, 2, Length));
  return 0;
}