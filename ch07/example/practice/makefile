#
# makefile
#
PROGS = swap.o swap.S.read swap.s.read

all: $(PROGS)

swap.o:
	gcc -c swap.c

swap.s.read: swap.o
	readelf -s swap.o > swap.s.read

swap.S.read: swap.o
	readelf -S swap.o > swap.S.read



.PHONY : clean
clean:
	rm -rf *.o
	rm -rf swap.*.obj
	rm -rf swap.*.read
	rm -rf swap.nm
	rm -rf swap.*.nm
	rm -rf elf.h
