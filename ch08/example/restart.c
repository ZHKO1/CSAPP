#include "./lib/csapp.h"

sigjmp_buf buf;

void handler(int s)
{
    siglongjmp(buf, 1);
}

int main(int argc, char *argv[], char *envp[])
{
    if (!sigsetjmp(buf, 1))
    {
        Signal(SIGINT, handler);
        Sio_puts("starting\n");
    }
    else
    {
        Sio_puts("restarting\n");
    }
    while (1)
    {
        Sleep(1);
        Sio_puts("processing...\n");
    }
    return 0;
}