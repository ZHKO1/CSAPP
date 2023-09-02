
#include <stdio.h>
#include <assert.h>
#include "../../lib/csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    char buf[MAXBUF] = "";
    int n;
    memset(buf, 0, MAXBUF);
    while ((n = Rio_readn(STDIN_FILENO, buf, MAXBUF)) != 0)
    {
        Rio_writen(STDOUT_FILENO, buf, strlen(buf));
        memset(buf, 0, MAXBUF);
    }

    return 0;
}