
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    struct addrinfo *p;
    struct addrinfo *listp;
    struct addrinfo hints;
    char buf[MAXLINE];
    char port[MAXLINE];
    int rc, flags;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s \n", gai_strerror(rc));
        exit(1);
    }

    flags = NI_NUMERICHOST | NI_NUMERICSERV;
    for (p = listp; p; p = p->ai_next)
    {
        memset(buf, 0, MAXLINE);
        memset(port, 0, MAXLINE);
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, port, MAXLINE, flags);
        // 这里注意当getaddrinfo第二个参数设为http
        // 可以看到port被设为80
        printf("%s:%s\n", buf, port);
    }

    Freeaddrinfo(listp);

    exit(0);

    return 0;
}