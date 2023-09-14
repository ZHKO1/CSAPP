
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

// 练习题11.2
int main(int argc, char *argv[], char *envp[])
{
    char dd[MAXLINE] = "";
    struct in_addr inaddr;
    uint32_t addr;
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <hex>\n", argv[0]);
        exit(0);
    }
    if (sscanf(argv[1], "%x", &addr) != 1)
    {
        fprintf(stderr, "%s is not <hex>\n", argv[1]);
        exit(0);
    };
    inaddr.s_addr = htonl(addr);
    const char *inet_ntop_result = inet_ntop(AF_INET, &inaddr, dd, MAXLINE);
    if (inet_ntop_result == NULL)
    {
        unix_error("inet_ntop error\n");
    }
    printf("%s\n", dd);

    return 0;
}