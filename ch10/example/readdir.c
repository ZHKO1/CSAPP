
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    DIR *streamp;
    struct dirent *dep;

    streamp = Opendir(argv[1]);

    errno = 0;
    while ((dep = readdir(streamp)) != NULL)
    {
        printf("Found file: %s\n", dep->d_name);
    }
    if (errno != 0)
    {
        unix_error("readdir error");
    }
    Closedir(streamp);
    return 0;
}