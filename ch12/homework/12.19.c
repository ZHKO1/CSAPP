#include "../../lib/csapp.h"
// 参考了https://zhuanlan.zhihu.com/p/351012714
int readcnt;

sem_t mutex;
sem_t w;
sem_t writer_r;

void *thread(void *vargp);
void reader(void);
void writer(void);

int main(int argc, char *argv[], char *envp[])
{
    sem_init(&mutex, 0, 1);
    sem_init(&w, 0, 1);
    sem_init(&writer, 0, 1);
    return;
}

void *thread(void *vargp)
{
    printf("Hello, world!\n");
    return NULL;
}

void reader(void)
{
    while (1)
    {

        P(&mutex);
        readcnt++;
        if (readcnt == 1)
            P(&w);
        V(&mutex);

        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void writer(void)
{
    while (1)
    {
        P(&writer_r);
        P(&w);
        V(&w);
        P(&mutex);
        V(&writer_r);        
        V(&mutex);
    }
}
