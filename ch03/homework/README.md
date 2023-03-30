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
A. rdx
B. rax
C. 15
## 3.66
NR(N) = 3n
NC(N) = 4n + 1
## 3.67
这里假设%rsp原来地址是104
A.
 0 存放 x
 8 存放 y
 16 存放 &z
 24 存放 z
B. 传递了地址 64 
C. 根据eval栈帧保存的x,y,&z来访问字段
D. 根据收到的参数 %rdi,也就是 64 来设置字段
E. 从process返回后根据如下对应地址来访问
 64 r.u0 
 72 r.u1
 80 r.z 
F. 调用方找到空间并将空间地址传递给被调用方，被调用方在该空间里存储数据
## 3.68
根据str2推断出
4 < B <= 8
2 < A <= 10
根据str1推断出
44 < A * B <= 46
A是9，B是5
## 3.69
CNT是7
```c
typedef struct {
  long idx;
  long x[4];
  // 第4~5行，原本我直接把%rax理解成&bp->a[i]，实际上还需要第六行的+8才是真正的&bp->a[i]，这里的8对应b_struct的first字段
}
```
## 3.70
A. 0 8 0 8
B. 16字节
C. up —> e2.x = *( up -> e2.next -> e1.p ) - up -> e2.next -> e1.y
## 3.71
参见3.71.c
## 3.72
A. S2 = S1 - (8n + 30) >> 4 << 4
 当n是偶数时，S1 - (8n + 16)
   用2k代表n，带入(8n + 30)/16，可以得到 30/16 + k = 1 + k,再乘以16，就是(8n + 16)
 当n是奇数时，S1 - (8n + 24)
   推理方式同上
B. (rsp + (1 << 4 - 1)) >> 4 换句话就是向上舍入到16的倍数
C. 最小的e1第一个想到的会是0，但如果e1是0，e2就会是16或者24，显然不太可能，因为数组p地址是16的倍数，所以最小的答案应该是1，此时e2是15（不需要考虑n是奇数，因为就算e2是23，也跟p是向上舍入16的倍数矛盾），所以n是偶数，那么数组p末尾地址也是16的倍数，显然s1%16是1
最大的e1第一个想到的是24，当e1是24，e2是0，那么数组p地址就是s2地址，都是16的倍数。
配合n是奇数，容易推断出s1%16是0
D. p地址根据16对齐。s2是保留了8n，同时也是16的最小倍数
## 3.73
参见3.73.c
## 3.74
参见3.74.c
## 3.75
基本忘光复数的知识了，所以搞不懂怎么做这个题...实际上如果理解复数定义，再配合函数输入输出，基本就能猜得差不多了