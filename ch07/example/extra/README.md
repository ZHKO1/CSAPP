# 参考
《程序员的自我修养——链接装载与库》

# 简单笔记
1. 生成重定向目标文件 [SimpleSection.o]
	gcc -c SimpleSection.c
  1). 粗略查看关键的段 [SimpleSection.h.obj]
	  objdump -h SimpleSection.o > SimpleSection.h.obj
  2). 查看反编译指令以及部分段的内容 [SimpleSection.ds.obj]
    objdump -d -s SimpleSection.o > SimpleSection.ds.obj
    >> 可以看到
    .data段 对应 全局初始化了的全局静态变量 和 局部静态遍历
    .rodata段 对应 字符串常量
2. 查看ELF文件结构
  1). 查看ELF文件头 [SimpleSection.h.read]
    readelf -h SimpleSection.o > SimpleSection.h.read
  2). 文件头参数和elf.h对比 [elf.h]
    cat /usr/include/elf.h > elf.h
  3). 查看真正的段表结构 [SimpleSection.S.read]
    readelf -S SimpleSection.o > SimpleSection.S.read
  4). 查看符号 [SimpleSection.nm]
    nm SimpleSection.o > SimpleSection.nm
  5). 查看符号表 [SimpleSection.s.read]
    readelf -s SimpleSection.o > SimpleSection.s.read
    
  
  



>> ELF文件头 跟 /user/include/elf.h 的Elf32_Ehdr数据结构对应
5. readelf查看ELF文件的段表结构
readelf -S SimpleSection.o
