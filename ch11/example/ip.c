
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    // 网络字节顺序 和 主机字节顺序 的切换
    uint32_t num = 0xFF0192AD;
    uint32_t result = htonl(num);
    unsigned char *c = (unsigned char *)&num;
    // 查看unit32_t类型数据的主机顺序是什么
    for (size_t i = 0; i < sizeof(uint32_t); i++)
    {
        printf("%.2x", (*(c + i)));
    }
    printf("\n");
    printf("num = %x; htonl(num)=%x\n", num, result);
    assert(num == ntohl(result));

    // IP地址和点分十进制串的互换
    char ip1[MAXLINE] = "127.0.0.1";
    uint32_t ip2 = 0;
    if (inet_pton(AF_INET, ip1, &ip2))
    {
        printf("ip1 = %s; ip2=%x\n", ip1, ip2);
    }
    else
    {
        unix_error("inet_pton error\n");
    };
    char ip3[MAXLINE] = "";
    const char *inet_ntop_result = inet_ntop(AF_INET, &ip2, ip3, MAXLINE);
    if (inet_ntop_result == NULL)
    {
        unix_error("inet_ntop error\n");
    }
    printf("ip1 = %s; ip3=%s\n", ip1, ip3);
    assert(strcmp(ip1, ip3) == 0);

    return 0;
}