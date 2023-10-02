#
# makefile
#
CC = gcc
CFLAGS = -Wall -g
LIB = ../../../lib/csapp.c

SRCS = $(wildcard ./cgi-bin/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
PROGS = $(patsubst %.c,%,$(SRCS))

TINYSRCS = $(wildcard *.c)
TINYOBJS = $(patsubst %.c,%.o,$(TINYSRCS))
TINYPROGS = $(patsubst %.c,%,$(TINYSRCS))

all: $(OBJS) csapp.o $(PROGS) $(TINYOBJS) $(TINYPROGS) copy

copy:
	(cp ../../../ch11/example/tiny_web/SWORDFISHII.jpg ./SWORDFISHII.jpg;)
	(cp ../../../ch11/example/tiny_web/video.mp4 ./video.mp4;)

csapp.o:
	$(CC) $(CFLAGS) -o $@ -c $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%: %.o csapp.o
	$(CC) $(CFLAGS) -o $@ $^ -lpthread


.PHONY : clean
clean:
	rm -rf *.o
	(cd cgi-bin; rm -rf *.o;)
	(rm video.mp4; rm SWORDFISHII.jpg;)
	find . -type f -executable -print0 | xargs -0 rm -f --
