#
# makefile
#
all: intc int1 intr

# 编译时打桩
mymalloc.o:
	gcc -DCOMPILETIME -o mymalloc.o -c mymalloc.c
intc: mymalloc.o
	gcc -I. -o intc int.c mymalloc.o
intc.test: intc
	./intc

# 链接时打桩
mymalloc_link.o:
	gcc -DLINKTIME -o mymalloc_link.o -c mymalloc.c
int.o:
	gcc -c int.c
int1: int.o mymalloc_link.o
	gcc -Wl,--wrap,malloc -Wl,--wrap,free -o int1 int.o mymalloc_link.o
int1.test: int1
	./int1

# 运行时打桩
mymalloc.so:
	gcc -DRUNTIME --shared -fPIC -o mymalloc.so mymalloc.c -ldl
intr:
	gcc -o intr int.c
intr.test: intr mymalloc.so
	LD_PRELOAD="./mymalloc.so" ./intr

test: intc.test int1.test intr.test

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.a
	find . -type f -executable -print0 | xargs -0 rm -f --
