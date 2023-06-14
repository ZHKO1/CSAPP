#include <stdio.h>
#include <assert.h>
char main;
void p2()
{
    assert(main == -13);
    printf("0x%x\n", main);
}
