#
# makefile
#
CC = gcc
LIB = ../../lib/csapp.c

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(OBJS) csapp.o $(PROGS)

csapp.o:
	$(CC) -o $@ -c $(LIB)

%.o: %.c
	$(CC) -o $@ -c $<

%: %.o csapp.o
	$(CC) -o $@ $^ -lpthread

test: $(PROGS_TEST)
	(make clean;)

%.test: %
	./$<


.PHONY : clean
clean:
	rm -rf *.o
	find . -type f -executable -print0 | xargs -0 rm -f --
