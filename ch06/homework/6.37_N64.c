/**
 * 感谢https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter6/6.37/网友的评论
 * https://paste.ubuntu.com/p/5Sxrm5ztTN/
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef unsigned int ui;
#define s 8
#define E 1
ui tt = 1;
typedef struct SET
{
    ui tag[E];
    bool valid[E];
    ui time[E];
} Set;
Set set[1 << s];
#define b 4
bool loc(ui pos)
{
    ui is = (pos >> b);
    ui ms = (ui)(~(((-1) >> s) << s));
    is = is & ms;
    ui tag = (pos >> (b + s));
    for (int i = 0; i < E; ++i)
    {
        if (set[is].tag[i] == tag && set[is].valid[i])
        {
            set[is].time[i] = ++tt;
            return true;
        }
    }
    ui ie = 0;
    for (int i = 0; i < E; ++i)
    {
        if (set[is].time[i] < set[is].time[ie])
        {
            ie = i;
        }
    }
    set[is].tag[ie] = tag;
    set[is].valid[ie] = true;
    set[is].time[ie] = ++tt;
    return false;
}

#define N 64
ui bias = 0x08000000;

void locCount(ui *pCntHit, ui *pCntMiss, ui pos)
{
    bool re = loc(pos);
    *pCntHit += re;
    *pCntMiss += !re;
}

void sumA(ui *pCntHit, ui *pCntMiss)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            locCount(pCntHit, pCntMiss, i * 4 * N + j * 4 + bias);
        }
    }
}
void sumB(ui *pCntHit, ui *pCntMiss)
{
    for (int j = 0; j < N; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            locCount(pCntHit, pCntMiss, i * 4 * N + j * 4 + bias);
        }
    }
}
void sumC(ui *pCntHit, ui *pCntMiss)
{
    for (int j = 0; j < N; j += 2)
    {
        for (int i = 0; i < N; i += 2)
        {
            locCount(pCntHit, pCntMiss, i * N * 4 + j * 4 + bias);
            locCount(pCntHit, pCntMiss, (i + 1) * N * 4 + j * 4 + bias);
            locCount(pCntHit, pCntMiss, i * N * 4 + (j + 1) * 4 + bias);
            locCount(pCntHit, pCntMiss, (i + 1) * N * 4 + (j + 1) * 4 + bias);
        }
    }
}

double test(void f(ui *, ui *))
{
    ui cntHit = 0, cntMiss = 0;
    memset(set, 0, sizeof(set));
    f(&cntHit, &cntMiss);
    return (double)cntMiss / (cntMiss + cntHit) * 100;
}

int main()
{
    printf("Array address=0x%08x  N=%d\n", bias, N);
    double sumA_miss_rate = test(sumA);
    printf("sumA : %lf%%\n", sumA_miss_rate);
    double sumB_miss_rate = test(sumB);
    printf("sumB : %lf%%\n", sumB_miss_rate);
    double sumC_miss_rate = test(sumC);
    printf("sumC : %lf%%\n", sumC_miss_rate);

    assert(25 == sumA_miss_rate);
    assert(100 == sumB_miss_rate);
    assert(50 == sumC_miss_rate);
    return 0;
}