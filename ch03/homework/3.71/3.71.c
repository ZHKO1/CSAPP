#include <stdio.h>
#include <string.h>
#define M 10

void good_echo()
{
    char str[M];
    char *ptr;
    while (ptr = fgets(str, M, stdin))
    {
        printf("%s", ptr);
    }
}

int main()
{
    good_echo();
    return 0;
}
