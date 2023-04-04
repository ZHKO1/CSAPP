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


objdump -d ctarget > ctarget.d

ctarget level 1
cat cl1.txt | ./hex2raw | ./ctarget -q
./hex2raw < cl1.txt > cl1
./ctarget -q -i cl1

ctarget level 2
gcc -c  cl2.s -o cl2.o
objdump -d cl2.o > cl2.d
cat cl2.txt | ./hex2raw | ./ctarget -q
./hex2raw < cl2.txt > cl2
./ctarget -q -i cl2

ctarget level 3
cat cl3.txt | ./hex2raw | ./ctarget -q
./hex2raw < cl3.txt > cl3
./ctarget -q -i cl3

objdump -d rtarget > rtarget.d

rtarget level 1
cat rl1.txt | ./hex2raw | ./rtarget -q
./hex2raw < rl1.txt > rl1
./rtarget -q -i rl1

rtarget level 2
cat rl2.txt | ./hex2raw | ./rtarget -q
./hex2raw < rl2.txt > rl2
./rtarget -q -i rl2