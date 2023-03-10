#include <stdio.h>
#include <assert.h>
typedef unsigned char *byte_pointer;

int is_little_endian()
{
    short num = 0x0001;
    byte_pointer start = (byte_pointer)&num;
    if (start[0] == 0x01)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    assert(is_little_endian());
    return 0;
}
