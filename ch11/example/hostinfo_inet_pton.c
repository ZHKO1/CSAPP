
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../../lib/csapp.h"

// 练习题11.4
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

        SA *ai_addr = p->ai_addr;
        char *sa_data = ai_addr->sa_data;
        uint16_t sin_port = *((uint16_t *)sa_data);
        struct in_addr sin_addr = *((struct in_addr *)((char *)sa_data + 2));
        const char *inet_ntop_result = inet_ntop(AF_INET, &sin_addr, buf, MAXLINE);
        if (inet_ntop_result == NULL)
        {
            unix_error("inet_ntop error\n");
        }
        printf("%s:%d\n", buf, ntohs(sin_port));
    }

    Freeaddrinfo(listp);

    exit(0);

    return 0;
}