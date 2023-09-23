
#include <stdio.h>
#include "../../lib/csapp.h"

// 本代码对应服务端，客户端见ch11/example/echoclient.c

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
    {
        exit(0);
    }
    printf("command: %s", buf);
}

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %ld bytes.buf=%sa", n, buf);
        Rio_writen(connfd, buf, n);
    }
}

int main(int argc, char *argv[], char *envp[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    fd_set read_set, ready_set;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while (1)
    {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &ready_set))
        {
            command();
        }
        if (FD_ISSET(listenfd, &ready_set))
        {
            clientlen = sizeof(struct sockaddr_storage);
            printf("Main: ready accept...\n");
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
            printf("Main: connected to (%s %s)\n", client_hostname, client_port);
            echo(connfd);
            printf("done echo\n");
            Close(connfd);
            printf("close connfd\n");
        }
    }
}