
#include <stdio.h>
#include "../../lib/csapp.h"

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %ld bytes.buf=%s\n", n, buf);
        Rio_writen(connfd, buf, n);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    printf("sizeof(struct sockaddr_storage) = %ld\n", sizeof(struct sockaddr_storage));
    printf("sizeof(struct sockaddr) = %ld\n", sizeof(struct sockaddr));
    printf("sizeof(struct sockaddr_in) = %ld\n", sizeof(struct sockaddr_in));
    char client_hostname[MAXLINE], client_port[MAXLINE];
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        printf("Accept\n");
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s %s)\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd);
        printf("Close\n");
    }
    exit(0);
}