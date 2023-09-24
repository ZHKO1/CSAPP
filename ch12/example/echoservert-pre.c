
#include <stdio.h>
#include "../../lib/csapp.h"
#include "./sbuf.h"
#define NTHREADS 4
#define SBUFSIZE 16

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;

// 本代码对应服务端，客户端见ch11/example/echoclient.c

int main(int argc, char *argv[], char *envp[])
{
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    pthread_t tid;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);

    for (i = 0; i < NTHREADS; i++)
    {
        Pthread_create(&tid, NULL, thread, NULL);
    }

    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        printf("ready accept...\n");
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("connected to (%s %s) get connfd=(%d)\n", client_hostname, client_port, connfd);
        sbuf_insert(&sbuf, connfd);
    }
    exit(0);
}

void *thread(void *vargp)
{
    pthread_t tid = pthread_self();
    Pthread_detach(tid);
    printf("thread(%ld) start\n", tid);
    while (1)
    {
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        Close(connfd);
        printf("thread(%ld) close connfd(%d)\n", tid, connfd);
    }
}