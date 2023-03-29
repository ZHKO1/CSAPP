## 3.58
```c
long decode2(long x, long y, long z)
{
  y -= z;
  x *= y;
  return (y << 63 >> 63) ^ x;
}
```
## 3.59
前提知识：补码乘法的位表示和无符号乘法一致
在这前提下，用无符号乘法的方式也能做到补码乘法
我们要做的是将64位的x符号扩展到128位，y也一样，让64位的x和64位的y无符号相乘，得到的位表示其实也是128位的补码乘积
x = 2^64 * xh + xl
y = 2^64 * yh + yl
x * y = (2^64 * xh + xl) * (2^64 * yh + yl)
x * y = 2^128 * xh * yh + 2^64(xh * yl + xl * yh) + xl * yl
这里x,y,xh,xl,yh,yl我们全都以无符号的视角来看待
这里xl * yl可能会有超过64位的溢出，这里称为xlyl_overflow
xh * yl + xl * yh这部分对应高64位，所以溢出了也无所谓
配合 p = 2^64 * ph + pl 就能看到对应关系
ph是xh * yl + xl * yh + xlyl_overflow
pl是xl * yl % 2^64
从汇编代码可以看到对应关系
yh %rdx
yl %rax
xh %rcx
xl %rsi
剩余部分就很好理解了
## 3.60
A. 
x %rdi
n %esi
result %rax
mask %rdx
B. result初始值是0，mask初始值是1
C. mask!=0
D. mask = mask << (n & 0xFF)
E. result |= x & mask;
F. 
0
1
!=0
mask << (n & 0xFF)
x & mask
## 3.61
比较流传的解法是这样
```c
long cread_alt(long *xp) {
  return (!xp ? 0 : *xp);
}
// 但是我看不懂为什么就能不获取指针对应内容
// 而且也没说明什么条件下才能编译出如下效果
cread_alt:
  movl $0, %eax
  testq %rdi, %rdi
  cmovne (%rdi), %rax
```
看了评论，才发现还真有人能做到
```c
long cread_alt(long *xp)
{
  long zero = 0;
  return *(xp ? xp : &zero);
}
// gcc -O1 -S test.c -fno-stack-protector
	movq	$0, -8(%rsp)
	leaq	-8(%rsp), %rax
	testq	%rdi, %rdi
	cmove	%rax, %rdi
	movq	(%rdi), %rax
	ret
```
## 3.62
```c
long switch3(long *p1, long *p2, mode_t action)
{
  long result = 0;
  switch(action){
    case MODE_A:
      result = *p2;
      *p2 = *p1;
      break;
    case MODE_B:
      result = *p1 + *p2;
      *p1 = result;
      break;
    case MODE_C:
      *p1 = 59;
      result = *p2;
      break;      
    case MODE_D:
      *p1 = *p2;
    case MODE_E:
      result = 27;
      break;
    default:
      result = 12;
  }
  return result;
}
```
## 3.63
```c
long switch_pro(long x, long n)
{
  long result = x;
  switch(n){
    case 0x3C:
    case 0x3E:
      result = 8 * x;
      break;
    case 0x3F:
      result = x >> 3;
      break;
    case 0x40:
      result = 15 * x ;
      x = result;
    case 0x41:
      x = x * x;
    default:
      result = 0x4b + x;
      break;
  }
  return result;
}
```
## 3.64
A + (5 * 13 * i + 13 * j + k) * 8
R,S,T 分别是7，5，13
## 3.65
## 3.66
## 3.67
## 3.68
## 3.69
## 3.70
## 3.71
## 3.72
## 3.73
## 3.74
## 3.75

