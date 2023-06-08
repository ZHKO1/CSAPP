#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99

SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%.o,$(SRCS))

all: prog2c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

libvector.a: addvec.o multvec.o
	ar rcs libvector.a addvec.o multvec.o

prog2c: libvector.a main2.o
	gcc -static -o prog2c main2.o ./libvector.a

test: prog2c
	./prog2c

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf prog2c
