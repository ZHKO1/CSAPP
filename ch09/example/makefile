#
# makefile
#
CC = gcc
LIB = 

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) -o $@ $<


# test: $(PROGS_TEST)

%.test: %
	./$<
	(make clean;)

.PHONY : clean
clean:
	rm -rf *.o
	find . -type f -executable -print0 | xargs -0 rm -f --
