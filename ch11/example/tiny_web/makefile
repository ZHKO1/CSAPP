#
# makefile
#
CC = gcc
LIB = ../../../lib/csapp.c

SRCS = $(wildcard ./cgi-bin/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(OBJS) csapp.o $(PROGS) tiny

csapp.o:
	$(CC) -o $@ -c $(LIB)

%.o: %.c
	$(CC) -o $@ -c $<

%: %.o csapp.o
	$(CC) -o $@ $^ -lpthread

tiny.o: tiny.c
	$(CC) -o $@ -c $<

tiny: tiny.o csapp.o
	$(CC) -o $@ $^ -lpthread


.PHONY : clean
clean:
	rm -rf *.o
	(cd cgi-bin; rm -rf *.o;)
	find . -type f -executable -print0 | xargs -0 rm -f --
