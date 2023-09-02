
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

#define BUFLEN 100

int touch(char *filename, char *content)
{
    int fd;
    umask(DEF_UMASK);
    fd = Open(filename, O_RDWR | O_CREAT | O_TRUNC, 0);
    Write(fd, content, strlen(content));
    return fd;
}

void readlineb_(char *buf, rio_t *rio, size_t n)
{
    memset(buf, 0, n);
    ssize_t rc = Rio_readlineb(rio, buf, n);
    printf("rio_readlineb_result=%ld buf=%s len=%ld\n", rc, buf, strlen(buf));
}

void read_n_btyes(char *buf, int fd, size_t n)
{
    memset(buf, 0, BUFLEN);
    ssize_t rc = Read(fd, buf, 6);
    printf("read_result=%ld buf=%s len=%ld\n", rc, buf, strlen(buf));
}

int main(int argc, char *argv[], char *envp[])
{
    char filename[20] = "GO LIKE HELL.txt";
    int fd = touch(filename, "There's a point.7,000 RPM where everything fades.\nThe machine becomes weightless.Just disappears.\nAnd all that's left is a body moving through space and time.\n7,000 RPM.That's where you meet it.It asks you a question.\nThe only question that matters.\n\"Who are you?\"");
    Lseek(fd, 0, SEEK_SET);

    rio_t rio;
    Rio_readinitb(&rio, fd);
    char buf[BUFLEN] = "";
    for (size_t i = 0; i < 7; i++)
    {
        readlineb_(buf, &rio, 100);
    }

    // 带缓冲的和不带缓冲的不能交叉使用
    // 这里演示交叉使用会有什么后果
    Lseek(fd, 0, SEEK_SET);
    Rio_readinitb(&rio, fd);
    readlineb_(buf, &rio, 100);
    read_n_btyes(buf, fd, 6); // 可以看到这里和预期不符，因为文件位置k早已到末尾

    Close(fd);
    remove(filename);

    // 原文示例 从标准输入复制一个文本文件到标准输出
    int n;
    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);

    return 0;
}