#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./lib/vec.h"

void inner7(vec_ptr u, vec_ptr v, data_t *dest)
{
  long i;
  long k = 6;
  long length = vec_length(u);
  long limit = length - k + 1;
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t sum = (data_t)0;

  for (i = 0; i < limit; i += k)
  {
    sum += udata[i] * vdata[i] +
           udata[i + 1] * vdata[i + 1] +
           udata[i + 2] * vdata[i + 2] +
           udata[i + 3] * vdata[i + 3] +
           udata[i + 4] * vdata[i + 4] +
           udata[i + 5] * vdata[i + 5];
  }

  for (; i < length; i++)
  {
    sum += udata[i] * vdata[i];
  }
  *dest = sum;
}

int main(int argc, char *argv[])
{
  vec_ptr u = new_vec(11);
  vec_ptr v = new_vec(11);

  data_t *arr = (data_t *)malloc(sizeof(data_t) * 4);
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;
  arr[3] = 3;
  arr[4] = 4;
  arr[5] = 5;
  arr[6] = 6;
  arr[7] = 7;
  arr[8] = 8;
  arr[9] = 9;
  arr[10] = 10;

  set_vec_start(u, arr);
  set_vec_start(v, arr);

  data_t res;
  inner7(u, v, &res);

  assert(res == 1 + 4 + 9 + 16 + 25 + 36 + 49 + 64 + 81 + 100);
  return 0;
}
