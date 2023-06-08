#
# makefile
#
PROGS = SimpleSection.o SimpleSection.h.obj SimpleSection.ds.obj SimpleSection.h.read elf.h SimpleSection.S.read SimpleSection.nm SimpleSection.s.read

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

SimpleSection.s.read: SimpleSection.o
	readelf -s SimpleSection.o > SimpleSection.s.read

SimpleSection.nm: SimpleSection.o
	nm SimpleSection.o > SimpleSection.nm

elf.h:
	cat /usr/include/elf.h > elf.h


.PHONY : clean
clean:
	rm -rf *.o
	rm -rf SimpleSection.*.obj
	rm -rf SimpleSection.*.read
	rm -rf SimpleSection.nm
	rm -rf SimpleSection.*.nm
	rm -rf elf.h
