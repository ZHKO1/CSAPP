
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

void read_n_btyes(char *buf, int fd, size_t n)
{
    memset(buf, 0, BUFLEN);
    ssize_t rc = Read(fd, buf, 6);
    printf("read_result=%ld buf=%s len=%ld\n", rc, buf, strlen(buf));
}

int main(int argc, char *argv[], char *envp[])
{
    char filename[10] = "hello.txt";
    int fd = touch(filename, "Super_Smash_Bros.");

    // 可以看到每次调用read函数，都会改变文件位置k
    Lseek(fd, 0, SEEK_SET);
    char buf[BUFLEN] = "";
    for (int i = 0; i < 4; i++)
    {
        read_n_btyes(buf, fd, 6);
    }
    Close(fd);
    remove(filename);

    // 从终端读文本行一般会返回不足值
    memset(buf, 0, BUFLEN);
    while (Read(STDIN_FILENO, buf, 8192) != 0)
    {
        Write(STDOUT_FILENO, buf, strlen(buf));
        memset(buf, 0, BUFLEN);
    }

    return 0;
}