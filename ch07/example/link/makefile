#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99

SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%.o,$(SRCS))

all: prog2c prog21 prog2r

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

# 与静态库链接
libvector.a: addvec.o multvec.o
	ar rcs libvector.a addvec.o multvec.o
prog2c: libvector.a main2.o
	gcc -static -o prog2c main2.o ./libvector.a
prog2c.test: prog2c
	./prog2c

# 动态链接共享库
libvector.so:
	gcc -shared -fpic -o libvector.so addvec.c multvec.c
prog21: libvector.so
	gcc -o prog21 main2.c ./libvector.so
prog21.test: prog21
	./prog21

# 从应用程序中加载和链接共享库
prog2r: libvector.so
	gcc -rdynamic -o prog2r dll.c -ldl
prog2r.test: prog2r
	./prog2r

test: prog2c.test prog21.test prog2r.test

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.a
	rm -rf prog2c
	rm -rf prog21
	rm -rf prog2r