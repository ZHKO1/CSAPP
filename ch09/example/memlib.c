#include "../../lib/csapp.h"
#include "memlib.h"

#define MAX_HEAP (20 * (1 << 20)) /* 20 MB */

static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

void mem_init()
{
    mem_heap = (char *)Malloc(MAX_HEAP);
    mem_brk = mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

void *mem_sbrk(int incr)
{
    char *old_brk = mem_brk;
    if ((incr < 0) || (mem_brk + incr) > mem_max_addr)
    {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed, Ran out of memory...\n");
        return (void *)-1;
    }
    mem_brk += incr;
    return (void *)old_brk;
}

void mem_free()
{
    Free((void *)mem_heap);
    mem_heap = NULL;
    mem_brk = NULL;
    mem_max_addr = NULL;
}
