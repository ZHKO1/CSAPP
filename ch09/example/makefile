#
# makefile
#
CC = gcc

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
PROGS_TEST = $(patsubst %.c,%.test,$(SRCS))

all: $(PROGS)
	(cd malloc;make)

%.o: %.c
	$(CC) -o $@ -c $^

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 
	
test: $(PROGS_TEST)
	(cd malloc;make test)

%.test: %
	./$<
	(make clean;)

.PHONY : clean
clean:
	rm -rf *.o
	find . -type f -executable -print0 | xargs -0 rm -f --
	(cd malloc;make clean)
