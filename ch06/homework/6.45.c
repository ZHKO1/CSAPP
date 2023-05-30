#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Length 100000

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
            if (i > j)
            {
                continue;
            }
            for (i1 = i; i1 < i + b; i1++)
            {
                for (j1 = j; j1 < j + b; j1++)
                {
                    dst[j1 * dim + i1] = src[i1 * dim + j1];
                    dst[i1 * dim + j1] = src[j1 * dim + i1];
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

int main(int argc, char *argv[])
{
    int N = 20;
    int a[Length] = {};
    for (int i = 0; i < Length; i++)
    {
        a[i] = i + 1;
    }
    // display(a, N);

    int p[Length] = {};
    transpose(p, a, N);
    // display(p, N);

    int p1[Length] = {};
    transpose_exercise(p1, a, N, 5);
    // display(p1, N);

    assert(memcmp(p, p1, Length * sizeof(int)) == 0);
    return 0;
}