#include "../../lib/csapp.h"
#include <assert.h>
#include <time.h> //用到clock()函数

#define MAXTHREADS 32

void *sum_mutex(void *vargp);

long psum[MAXTHREADS];
long nelems_per_thread;
sem_t mutex;

int main(int argc, char **argv)
{
    long i, nelems, log_nelems, nthreads, myid[MAXTHREADS];
    pthread_t tid[MAXTHREADS];
    int begintime, endtime;
    memset(psum, 0, MAXTHREADS);

    if (argc != 3)
    {
        printf("Usage: %s <nthreads> <log_nelems>\n", argv[0]);
        exit(0);
    }

    nthreads = atoi(argv[1]);
    log_nelems = atoi(argv[2]);
    nelems = (1L << log_nelems);
    nelems_per_thread = nelems / nthreads;
    printf("线程数=%ld 每线程计算数量=%ld\n", nthreads, nelems_per_thread);
    sem_init(&mutex, 0, 1);

    begintime = clock();

    for (i = 0; i < nthreads; i++)
    {
        myid[i] = i;
        Pthread_create(&tid[i], NULL, sum_mutex, &myid[i]);
    }
    for (i = 0; i < nthreads; i++)
    {
        Pthread_join(tid[i], NULL);
    }

    long gsum = 0;
    for (i = 0; i < nthreads; i++)
    {
        gsum += psum[i];
    }
    // printf("gsum=%ld (nelems * (nelems - 1) / 2)=%ld\n", gsum, sum);
    endtime = clock();
    printf("多线程 Running Time: %fs\n", (double)(endtime - begintime) / CLOCKS_PER_SEC);

    long sum = 0;
    begintime = clock();
    for (i = 0; i < nelems; i++)
    {
        sum += i;
    }
    endtime = clock();
    printf("单线程 Running Time: %fs\n", (double)(endtime - begintime) / CLOCKS_PER_SEC);
    assert(gsum == sum);

    exit(0);
}

void *sum_mutex(void *vargp)
{
    long myid = *((long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start + nelems_per_thread;
    long i;

    long sum;

    for (i = start; i < end; i++)
    {
        sum += i;
    }
    psum[myid] = sum;
    return NULL;
}