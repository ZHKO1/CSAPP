# 只有单个mstore.c
汇编文件 mstore.s
gcc -Og -S mstore.c
目标代码 mstore.o
gcc -Og -c mstore.c
从 mstore.o 反汇编
objdump -d mstore.o

# mstore.c 和 main.c
```shell
gcc -Og -og prog main.c mstore.c
objdump -d prog

# 使用gdb查看函数multstore所处地址开始的14个十六进制格式表示
gcc -Og -g -o prog main.c mstore.c
gdb prog
(gdb) file prog
(gdb) x/14xb multstore
```
