#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define MATRIX_N 1024
#define MEM_SIZE (sizeof(int) * MATRIX_N * MATRIX_N)
#define LOOP 1000
#define BLOCK 8

void randomize(void *mem, size_t size)
{
  int rnd = open("/dev/urandom", O_RDONLY);
  read(rnd, mem, size);
  close(rnd);
}

void transpose(int *dst, int *src, int dim)
{
  int i, j;
  for (i = 0; i < dim; i++)
  {
    for (j = 0; j < dim; j++)
    {
      dst[j * dim + i] = src[i * dim + j];
    }
  }
}

void transpose_exercise(int *dst, int *src, int dim, int b)
{
  int i, j, i1, j1;
  for (i = 0; i <= dim - b; i += b)
  {
    for (j = 0; j <= dim - b; j += b)
    {
      for (i1 = i; i1 < i + b; i1++)
      {
        for (j1 = j; j1 < j + b; j1++)
        {
          dst[j1 * dim + i1] = src[i1 * dim + j1];
        }
      }
    }
  }
  int i_offset = i;
  int j_offset = j;
  for (j = 0; j < j_offset; j += b)
  {
    for (i = i_offset; i < dim; i++)
    {
      for (j1 = j; j1 < j + b; j1++)
      {
        dst[j1 * dim + i] = src[i * dim + j1];
        dst[i * dim + j1] = src[j1 * dim + i];
      }
    }
  }
  for (i = i_offset; i < dim; i++)
  {
    for (j = j_offset; j < dim; j++)
    {
      dst[j * dim + i] = src[i * dim + j];
    }
  }
}

void display(int *arr, int dim)
{
  int i, j;
  for (i = 0; i < dim; i++)
  {
    for (j = 0; j < dim; j++)
    {
      int value = arr[i * dim + j];
      printf("%-3d ", value);
    }
    printf("\n");
  }
  printf("over\n");
}

void test(void)
{
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);
  randomize((void *)s, MEM_SIZE);

  transpose(d, s, MATRIX_N);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == d[j * MATRIX_N + i]);

  memset(d, 0, MATRIX_N);
  transpose_exercise(d, s, MATRIX_N, BLOCK);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == d[j * MATRIX_N + i]);

  free((void *)d);
  free((void *)s);
}

void prof(void)
{
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int c = 0; c < LOOP; c++)
    transpose(d, s, MATRIX_N);

  gettimeofday(&end, NULL);
  long timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
  printf("transpose time =%f 秒\n", (double)timeuse / 1000000);

  free((void *)d);
  free((void *)s);
}

void prof_effect(void)
{
  int *d = (int *)malloc(MEM_SIZE);
  int *s = (int *)malloc(MEM_SIZE);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int c = 0; c < LOOP; c++)
    transpose_exercise(d, s, MATRIX_N, BLOCK);

  gettimeofday(&end, NULL);
  long timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
  printf("transpose_exercise time =%f 秒\n", (double)timeuse / 1000000);

  free((void *)d);
  free((void *)s);
}

int main(int argc, char *argv[])
{
  test();

  // prof();
  // prof_effect();

  return 0;
}