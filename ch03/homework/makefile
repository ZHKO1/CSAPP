#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=gnu99
SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)
	(cd 3.71; make)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(PROGS_TEST)
	(cd 3.71; make test)

%.test: %
	./$<
	rm -f $<

.PHONY : clean
clean:
	(cd 3.71; make clean)
	find . -type f -executable -print0 | xargs -0 rm -f --
