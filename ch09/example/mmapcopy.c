/*
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    struct stat stat;
    int fd = 0;

    if (argc != 2)
    {
        printf("usage: %s <filename>\n", argv[0]);
        return 0;
    }
    fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0)
    {
        printf("open error\n");
        return -1;
    }
    fstat(fd, &stat);

    char *bufp;
    size_t size = stat.st_size;
    bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (bufp == MAP_FAILED)
    {
        printf("mmap error\n");
        return -1;
    }
    // printf("%s", bufp);
    write(1, bufp, size);
    close(fd);
    return 0;
}