#include <stdio.h>
#include <assert.h>

typedef enum
{
    NEG,
    ZERO,
    POS,
    OTHER
} range_t;

range_t find_range(float x)
{
    asm("vxorps %xmm1, %xmm1, %xmm1\n\t"
        "vucomiss %xmm1, %xmm0\n\t"
        "jp .OTHER\n\t"
        "ja .POS\n\t"
        "je .ZERO\n\t"
        "jb .NEG\n\t"
        ".NEG:\n\t"
        "movl $0, %eax\n\t"
        "jmp .DONE\n\t"
        ".ZERO:\n\t"
        "movl $1, %eax\n\t"
        "jmp .DONE\n\t"
        ".POS:\n\t"
        "movl $2, %eax\n\t"
        "jmp .DONE\n\t"
        ".OTHER:\n\t"
        "movl $3, %eax\n\t"
        "jmp .DONE\n\t"
        ".DONE:\n\t");
}

int main()
{
    range_t n = NEG, z = ZERO, p = POS, o = OTHER;
    assert(o == find_range(0.0 / 0.0));
    assert(n == find_range(-2.3));
    assert(z == find_range(0.0));
    assert(p == find_range(3.33));
    return 0;
}
