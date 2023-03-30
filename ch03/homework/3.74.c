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
        "movl $0, -8(%rsp)\n\t"
        "movl $1, -16(%rsp)\n\t"
        "movl $2, -24(%rsp)\n\t"
        "movl $3, -32(%rsp)\n\t"
        "vucomiss %xmm1, %xmm0\n\t"
        "cmova -24(%rsp), %rax\n\t"
        "cmove -16(%rsp), %rax\n\t"
        "cmovb -8(%rsp), %rax\n\t"
        "cmovp -32(%rsp), %rax\n\t"
    );
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
