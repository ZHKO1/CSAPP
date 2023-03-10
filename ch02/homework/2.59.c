#include <stdio.h>
#include <assert.h>
typedef unsigned char *byte_pointer;

int main()
{
    unsigned int x = 0x89ABCDEF;
    unsigned int y = 0x76543210;
    unsigned int z = 0x765432EF;
    assert(z == (x & 0xFF) | (y & ~0xFF));
    return 0;
}
