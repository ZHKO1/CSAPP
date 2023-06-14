#
# makefile
#
PROGS = swap.o swap.S.read swap.s.read swap.r.obj

all: $(PROGS)

swap.o:
	gcc -static -o swap.o -c swap.c

swap.r.obj: swap.o
	objdump -r swap.o > swap.r.obj

swap.t.obj: swap.o
	objdump -t swap.o > swap.t.obj

swap.s.read: swap.o
	readelf -s swap.o > swap.s.read

swap.S.read: swap.o
	readelf -S swap.o > swap.S.read

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf *.*.obj
	rm -rf *.*.read
	rm -rf *.nm
	rm -rf *.*.nm
	rm -rf elf.h
