#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=c99
SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(PROGS_TEST)

%.test: %
	./$<

.PHONY : clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --
