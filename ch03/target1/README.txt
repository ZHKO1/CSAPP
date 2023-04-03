This file contains materials for one instance of the attacklab.

Files:

    ctarget

Linux binary with code-injection vulnerability.  To be used for phases
1-3 of the assignment.

    rtarget

Linux binary with return-oriented programming vulnerability.  To be
used for phases 4-5 of the assignment.

     cookie.txt

Text file containing 4-byte signature required for this lab instance.

     farm.c

Source code for gadget farm present in this instance of rtarget.  You
can compile (use flag -Og) and disassemble it to look for gadgets.

     hex2raw

Utility program to generate byte sequences.  See documentation in lab
handout.


objdump -d ctarget > ctarget.disassemble

ctarget level 1
./hex2raw < ctarget.l1.txt > cl1
./ctarget -q -i cl1

ctarget level 2

gcc -c  cl2.s -o cl2.o
objdump -d cl2.o > cl2.d
./hex2raw < ctarget.l2.txt > cl2
./ctarget -q -i cl2

ctarget level 3
59b997fa
35 39 62 39 39 37 66 61 00