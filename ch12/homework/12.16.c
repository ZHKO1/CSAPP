#include "../../lib/csapp.h"

void *thread(void *vargp);

int main(int argc, char *argv[], char *envp[])
{
    pthread_t tid;
    int nthreads;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <nthreads>\n", argv[0]);
        exit(0);
    }

    nthreads = atoi(argv[1]);
    for (int i = 0; i < nthreads; i++)
    {
        Pthread_create(&tid, NULL, thread, (void *)i);
    }
    Pthread_join(tid, NULL);
    exit(0);
}

void *thread(void *vargp)
{
    int myid = (int)vargp;
    printf("%d: Hello, world!\n", myid);
    return NULL;
}