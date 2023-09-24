#
# makefile
#
CC = gcc
LIB = ../../lib/csapp.c

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
PROGS_ALL = $(patsubst %.c,%,$(SRCS))
EXCLUDES = echo-cnt sbuf
PROGS = $(filter-out ${EXCLUDES},$(PROGS_ALL))
PROGS_TEST = $(patsubst %,%.test,$(PROGS))

all: $(OBJS) csapp.o $(PROGS)

csapp.o:
	$(CC) -o $@ -c $(LIB)

%.o: %.c
	$(CC) -o $@ -c $<

%: %.o csapp.o
	$(CC) -o $@ $^ -lpthread

echoservert-pre: echoservert-pre.o echo-cnt.o sbuf.o csapp.o
	$(CC) -o $@ $^ -lpthread

test: $(PROGS_TEST)
	(make clean;)

%.test: %
	./$<


.PHONY : clean
clean:
	rm -rf *.o
	find . -type f -executable -print0 | xargs -0 rm -f --
