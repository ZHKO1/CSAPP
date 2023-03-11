#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)
	(cd float_bits; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(PROGS_TEST)
	(cd float_bits; make test)

%.test: %
	./$<
	rm -f $<

.PHONY : clean
clean:
	(cd float_bits; make clean)
	find . -type f -executable -print0 | xargs -0 rm -f --
