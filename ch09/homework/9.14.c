
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include "../../lib/csapp.h"

void test(char *filename, char *content)
{
    int fd;
    char buf[20];
    fd = Open(filename, O_RDONLY, 0);
    Read(fd, buf, strlen(content));
    assert(!strncmp(buf, content, strlen(content)));
}

int touch(char *filename, char *content)
{
    int fd;
    umask(DEF_UMASK);
    fd = Open(filename, O_WRONLY | O_CREAT | O_TRUNC, DEF_MODE);
    Write(fd, content, strlen(content));
    Close(fd);
}

int main(int argc, char *argv[], char *envp[])
{
    char filename[10] = "hello.txt";
    touch(filename, "Hello, world!");
    test(filename, "Hello, world!");
    struct stat stat;
    int fd = 0;
    fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        printf("open error\n");
        return -1;
    }
    fstat(fd, &stat);

    char *bufp;
    size_t size = stat.st_size;
    bufp = Mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    *bufp = 'J';

    test(filename, "Jello, world!");

    Munmap(bufp, size);
    close(fd);
    remove(filename);
    return 0;
}