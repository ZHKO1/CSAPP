#include "../../lib/csapp.h"

volatile sig_atomic_t pid;

void sigchld_handler(int s)
{
    int olderrno = errno;
    pid = Waitpid(-1, NULL, 0);
    errno = olderrno;
}

void sigint_handler(int s)
{
}

int main(int argc, char *argv[], char *envp[])
{
    sigset_t mask, prev;
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGINT, sigint_handler);
    Sigemptyset(&mask);
    Sigaddset(&mask, SIGCHLD);

    int index = 0;
    while (1)
    {
        // printf("sleep start %d \n", index++);
        // sleep(5);
        // printf("sleep end\n");
        Sigprocmask(SIG_BLOCK, &mask, &prev);
        if (Fork() == 0)
        {
            exit(0);
        }

        pid = 0;
        while (!pid)
            Sigsuspend(&prev);

        Sigprocmask(SIG_SETMASK, &prev, NULL);

        printf(".");
        // fflush(stdout);
    }
    return 0;
}