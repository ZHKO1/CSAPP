gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o
gcc -c main2.c
gcc -static -o prog2c main2.o ./libvector.a