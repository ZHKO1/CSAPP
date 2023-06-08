#
# makefile
#
PROGS = SimpleSection.o SimpleSection.h.obj SimpleSection.ds.obj SimpleSection.h.read elf.h SimpleSection.S.read

all: $(PROGS)

SimpleSection.o:
	gcc -c SimpleSection.c

SimpleSection.h.obj: SimpleSection.o
	objdump -h SimpleSection.o > SimpleSection.h.obj

SimpleSection.ds.obj: SimpleSection.o
	objdump -d -s SimpleSection.o > SimpleSection.ds.obj

SimpleSection.h.read: SimpleSection.o
	readelf -h SimpleSection.o > SimpleSection.h.read

SimpleSection.S.read: SimpleSection.o
	readelf -S SimpleSection.o > SimpleSection.S.read

elf.h:
	cat /usr/include/elf.h > elf.h


.PHONY : clean
clean:
	rm -rf *.o
	rm -rf SimpleSection.*.obj
	rm -rf SimpleSection.*.read
	rm -rf elf.h
