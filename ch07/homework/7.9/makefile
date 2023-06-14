#
# makefile
#
PROGS = main main.d.obj test

all: $(PROGS)

main:
	gcc -o main foo6.c bar6.c

test: main
	./main

main.d.obj: main
	objdump -d main > main.d.obj

.PHONY : clean
clean:
	rm -rf main
	rm -rf *.*.obj
