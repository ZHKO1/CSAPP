#
# makefile
#
CC = gcc
LIB = ../../../lib/csapp.c

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

MEM = mm.c memlib.c  malloc.c
MEM_PROGS = $(patsubst %.c,%.o,$(MEM))

all: csapp.o malloc

csapp.o:
	$(CC) -o $@ -c $(LIB)

%.o: %.c
	$(CC) -o $@ -c $^

malloc: csapp.o $(MEM_PROGS)
	$(CC) -o $@ $^ -lpthread

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 
	
test: malloc
	./malloc
	make clean


.PHONY : clean
clean:
	rm -rf *.o
	find . -type f -executable -print0 | xargs -0 rm -f --
