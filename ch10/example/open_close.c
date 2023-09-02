
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

void test(char *filename, char *content)
{
    int fd;
    char buf[20];
    fd = Open(filename, O_RDONLY, 0);
    printf("test open fd=%d\n", fd);
    Read(fd, buf, strlen(content));
    assert(!strncmp(buf, content, strlen(content)));
    Close(fd);
}

int touch(char *filename, char *content)
{
    int fd;
    umask(DEF_UMASK);
    fd = Open(filename, O_WRONLY | O_CREAT, 0);
    printf("touch open fd=%d\n", fd);
    Write(fd, content, strlen(content));
    Close(fd);
}

int main(int argc, char *argv[], char *envp[])
{
    char filename[10] = "hello.txt";
    touch(filename, "Hello, world!");
    test(filename, "Hello, world!");

    // 可以看到因为有O_TRUNC，所以hello.text内容是FUCK
    // 如果删掉O_TRUNC，则hello.text的内容变成FUCKo, world!
    touch(filename, "FUCK");
    test(filename, "FUCK");

    remove(filename);
    return 0;
}