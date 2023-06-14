## 7.6
是练习题7.1的变种，先谈7.1
实际编译后得到的符号表跟书后答案有所不同，尤其是buf和bufp0
buf我理解应该是UND，readelf也是UND，然而原书答案是.data。
bufp0从readelf来看是.data.rel节，原书答案是.data
这里7.6题网友编译查看bufp0也是得到.data
所以bufp0可能是跟gcc版本有关

## 7.9
我的环境会输出0xfffffff3
1. 显然，在main所在的地址开始的第一个字节就是第一条指令的第一个字节
2. bar6.c里对main的声明是char类型，只有一个字节。通过反汇编能看到第一个指令是endbr64指令。所以第一个字节是f3
3. printf函数里以%x输出，也就是以十六进制的无符号整数来输出，所以f3会变成0xfffffff3

## 7.13
A.
  whereis libc.a
  ar t /usr/lib/x86_64-linux-gnu/libc.a  | wc -l
  至于libm.a 我环境下报错了，具体参见https://blog.csdn.net/aurora0_0/article/details/84547376
B.
  不同，可以用md5验证结果
C.
  ldd main
  

