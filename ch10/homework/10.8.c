
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    struct stat stat;
    char *type, *readok;

    Fstat(atoi(argv[1]), &stat);

    if (S_ISREG(stat.st_mode))
    {
        type = "regular";
    }
    else if (S_ISDIR(stat.st_mode))
    {
        type = "directory";
    }
    else
    {
        type = "other";
    }

    if ((stat.st_mode & S_IRUSR))
    {
        readok = "yes";
    }
    else
    {
        readok = "no";
    }

    printf("type= %s, read: %s\n", type, readok);

    return 0;
}