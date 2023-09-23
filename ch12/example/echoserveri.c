
#include <stdio.h>
#include "../../lib/csapp.h"

// 本代码对应服务端，客户端见ch11/example/echoclient.c

void sigchld_handler(int sig)
{
    while (waitpid(-1, 0, WNOHANG))
    {
    }
    return;
}

void echo(int connfd, pid_t pid)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("child(%d): server received %ld bytes.buf=%s\n", pid, n, buf);
        Rio_writen(connfd, buf, n);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(argv[1]);
    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        printf("Main: ready accept...\n");
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Main: connected to (%s %s)\n", client_hostname, client_port);
        pid_t pid;
        if ((pid = Fork()) == 0)
        {
            int pid = (int)getpid();
            Close(listenfd);
            printf("Child(%d): close listenfd\n", pid);
            echo(connfd, pid);
            printf("Child(%d): done echo\n", pid);
            Close(connfd);
            printf("Child(%d): close connfd\n", pid);
            exit(0);
        }
        Close(connfd);
        printf("Main: close connfd of pid(%d)\n", (int)pid);
    }
    exit(0);
}