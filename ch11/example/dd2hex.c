
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

// 练习题11.3
int main(int argc, char *argv[], char *envp[])
{
    struct in_addr inaddr;
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <dd>\n", argv[0]);
        exit(0);
    }
    int rc = inet_pton(AF_INET, argv[1], &inaddr);
    if (rc == 0)
    {
        app_error("inet_pton error: 点分十进制字符串不合法\n");
    }
    else if (rc < 0)
    {
        unix_error("inet_pton error\n");
    };
    printf("0x%x\n", ntohl(inaddr.s_addr));

    return 0;
}