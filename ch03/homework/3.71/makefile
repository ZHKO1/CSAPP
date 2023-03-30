#
# makefile
#
CC = gcc
CFLAGS = -m64 -std=gnu99
SRCS = $(wildcard *.*.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test:

.PHONY: clean
clean:
	find . -type f -executable -print0 | xargs -0 rm -f --

# vim:ft=make
#
