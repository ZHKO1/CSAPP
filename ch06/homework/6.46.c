#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define MATRIX_N 1024
#define MEM_SIZE (sizeof(int) * MATRIX_N * MATRIX_N)
#define LOOP 1000
#define BLOCK 8

void randomize(int *arr, int N)
{
  srand(time(0));

  int i, j;
  for (i = 0; i <= N - 1; i++)
    for (j = 0; j <= N - 1; j++)
      arr[i * N + j] = rand() % 2;
}

void col_convert(int *G, int dim)
{
  int i, j;
  for (i = 0; i < dim; i++)
  {
    for (j = 0; j < dim; j++)
    {
      G[j * dim + i] = G[j * dim + i] || G[i * dim + j];
    }
  }
}

void col_convert_exercise(int *G, int dim, int b)
{
  int i, j, i1, j1;
  for (i = 0; i <= dim - b; i += b)
  {
    for (j = 0; j <= dim - b; j += b)
    {
      if (i > j)
      {
        continue;
      }
      for (i1 = i; i1 < i + b; i1++)
      {
        for (j1 = j; j1 < j + b; j1++)
        {
          int value = G[i1 * dim + j1] || G[j1 * dim + i1];
          G[j1 * dim + i1] = value;
          G[i1 * dim + j1] = value;
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
        int value = G[i * dim + j1] || G[j1 * dim + i];
        G[j1 * dim + i] = value;
        G[i * dim + j1] = value;
      }
    }
  }
  for (i = i_offset; i < dim; i++)
  {
    for (j = i; j < dim; j++)
    {
      int value = G[i * dim + j] || G[j * dim + i];
      G[j * dim + i] = value;
      G[i * dim + j] = value;
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
  int *s = (int *)malloc(MEM_SIZE);
  int *e = (int *)malloc(MEM_SIZE);

  randomize(s, MATRIX_N);
  memcpy(e, s, MEM_SIZE);

  col_convert(s, MATRIX_N);
  col_convert_exercise(e, MATRIX_N, BLOCK);

  for (int i = 0; i < MATRIX_N; i++)
    for (int j = 0; j < MATRIX_N; j++)
      assert(s[i * MATRIX_N + j] == e[i * MATRIX_N + j]);

  free((void *)s);
  free((void *)e);
}

void prof(void)
{
  int *s = (int *)malloc(MEM_SIZE);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int c = 0; c < LOOP; c++)
    col_convert(s, MATRIX_N);

  gettimeofday(&end, NULL);
  long timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
  printf("transpose time =%f 秒\n", (double)timeuse / 1000000);

  free((void *)s);
}

void prof_effect(void)
{
  int *s = (int *)malloc(MEM_SIZE);

  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int c = 0; c < LOOP; c++)
    col_convert_exercise(s, MATRIX_N, BLOCK);

  gettimeofday(&end, NULL);
  long timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
  printf("transpose_exercise time =%f 秒\n", (double)timeuse / 1000000);

  free((void *)s);
}

int main(int argc, char *argv[])
{
  test();

  // prof();
  // prof_effect();

  return 0;
}