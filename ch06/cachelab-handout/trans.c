/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void display(int N, int M, int arr[N][M]);
void transpose_32_32(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]);
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
  if (M == 32 && N == 32)
  {
    transpose_32_32(M, N, A, B);
  }
  if (M == 64 && N == 64)
  {
    transpose_64_64(M, N, A, B);
  }
  if (M == 61 && N == 67)
  {
    transpose_61_67(M, N, A, B);
  }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, tmp;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
    {
      tmp = A[i][j];
      B[j][i] = tmp;
    }
  }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
  /* Register your solution function */
  registerTransFunction(transpose_submit, transpose_submit_desc);

  /* Register any additional transpose functions */
  registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
  int i, j;

  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; ++j)
    {
      if (A[i][j] != B[j][i])
      {
        return 0;
      }
    }
  }
  return 1;
}

void transpose_32_32(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, b1, b2;
  int b = 8;
  for (i = 0; i <= N - b; i += b)
  {
    for (j = 0; j <= M - b; j += b)
    {
      for (b1 = 1; b1 <= b; b1++)
      {
        for (b2 = 1; b2 <= b; b2++)
        {
          B[j + ((b2 + b1 - 1) % b)][i + b1 - 1] = A[i + b1 - 1][j + ((b2 + b1 - 1) % b)];
        }
      }
    }
  }
}

/*
 * 参考学习了 zhuanlan.zhihu.com/p/484657229
 * 这道题本质上就是如何在4*4的基础上能更好地利用缓存一行能放8个的优势
 */
void transpose_64_64(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, k;
  int b = 8;
  int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  for (i = 0; i <= N - b; i += b)
  {
    for (j = 0; j <= M - b; j += b)
    {
      // 假设A的8*8方格里四个4*4方格，左上，右上，左下，右下，分别为A1，A2，A3，A4
      // 假设B的8*8方格里四个4*4方格，左上，右上，左下，右下，分别为B1，B2，B3，B4，显然B1应该置放A1’（A1的置换），B2应该置放A3'，B3应该置放A2'，B4应该置放A4'

      // 第一步是将A1，A2先放到B的B1，B2上,同时进行置换处理，此时B1和B2分别置放A1’, A2’
      for (k = i; k < i + 4; k++)
      {
        tmp0 = A[k][j + 0];
        tmp1 = A[k][j + 1];
        tmp2 = A[k][j + 2];
        tmp3 = A[k][j + 3];

        tmp4 = A[k][j + 4];
        tmp5 = A[k][j + 5];
        tmp6 = A[k][j + 6];
        tmp7 = A[k][j + 7];

        B[j + 0][k] = tmp0;
        B[j + 1][k] = tmp1;
        B[j + 2][k] = tmp2;
        B[j + 3][k] = tmp3;

        B[j + 0][k + 4] = tmp4;
        B[j + 1][k + 4] = tmp5;
        B[j + 2][k + 4] = tmp6;
        B[j + 3][k + 4] = tmp7;
      }
      // 第二步
      // 1). 将B2的A2'放到B3上
      // 2). 将A3放到B2上，同时置换成A3'
      for (k = j; k < j + 4; k++)
      {
        tmp0 = A[i + 4][k];
        tmp1 = A[i + 5][k];
        tmp2 = A[i + 6][k];
        tmp3 = A[i + 7][k];

        tmp4 = B[k][i + 4];
        tmp5 = B[k][i + 5];
        tmp6 = B[k][i + 6];
        tmp7 = B[k][i + 7];

        B[k][i + 4] = tmp0;
        B[k][i + 5] = tmp1;
        B[k][i + 6] = tmp2;
        B[k][i + 7] = tmp3;

        B[k + 4][i + 0] = tmp4;
        B[k + 4][i + 1] = tmp5;
        B[k + 4][i + 2] = tmp6;
        B[k + 4][i + 3] = tmp7;
      }
      // 第三步 将A4放到B4上，同时置换成A4'
      for (k = i + 4; k < i + 8; k++)
      {
        tmp0 = A[k][j + 4];
        tmp1 = A[k][j + 5];
        tmp2 = A[k][j + 6];
        tmp3 = A[k][j + 7];

        B[j + 4][k] = tmp0;
        B[j + 5][k] = tmp1;
        B[j + 6][k] = tmp2;
        B[j + 7][k] = tmp3;
      }
    }
  }
  // display(M, N, A);
  // display(N, M, B);
}

void display(int M, int N, int arr[N][M])
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
    {
      int value = arr[i][j];
      printf("%-5x ", value);
    }
    printf("\n");
  }
  printf("over\n");
}

void transpose_61_67(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, i1, j1;
  int b = 17;
  for (i = 0; i < N; i += b)
  {
    for (j = 0; j < M; j += b)
    {
      for (i1 = i; i1 < i + b && i1 < N; i1++)
      {
        for (j1 = j; j1 < j + b && j1 < M; j1++)
        {
          B[j1][i1] = A[i1][j1];
        }
      }
    }
  }
}