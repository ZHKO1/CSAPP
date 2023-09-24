#include "../../lib/csapp.h"

void *thread(void *vargp);

volatile long cnt = 0;

// 信号量同步操作，否则会出问题
sem_t mutex;

int main(int argc, char **argv)
{
    long niters;
    pthread_t tid1, tid2, tid3;
    if (argc != 2)
    {
        printf("usage: %s <niters>\n", argv[0]);
        exit(0);
    }

    // 信号量同步操作，否则会出问题
    Sem_init(&mutex, 0, 1);
    niters = atoi(argv[1]);

    Pthread_create(&tid1, NULL, thread, &niters);
    Pthread_create(&tid2, NULL, thread, &niters);
    Pthread_create(&tid3, NULL, thread, &niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);
    Pthread_join(tid3, NULL);
    if (cnt != (3 * niters))
    {
        printf("BOOM! cnt=%ld\n", cnt);
    }
    else
    {
        printf("OK cnt=%ld\n", cnt);
    }
    exit(0);
}

void *thread(void *vargp)
{
    long i, niters = *((long *)vargp);
    for (i = 0; i < niters; i++)
    {
        // 信号量同步操作，否则会出问题
        P(&mutex);

        cnt++;

        // 信号量同步操作，否则会出问题
        V(&mutex);
    }
    return NULL;
}