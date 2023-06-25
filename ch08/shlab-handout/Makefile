# Makefile for the CS:APP Shell Lab

TEAM = NOBODY
VERSION = 1
HANDINDIR = /afs/cs/academic/class/15213-f02/L5/handin
DRIVER = ./sdriver.pl
TSH = ./tsh
TSHREF = ./tshref
TSHARGS = "-p"
CC = gcc
CFLAGS = -Wall -O2
FILES = $(TSH) ./myspin ./mysplit ./mystop ./myint

all: $(FILES)

##################
# Handin your work
##################
handin:
	cp tsh.c $(HANDINDIR)/$(TEAM)-$(VERSION)-tsh.c


##################
# Regression tests
# 这里我的测试方式是make rtest生成官方答案，再执行make clean 以及 make test生成自己的多个test输出，最后git diff对比
##################

test: all test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 test11 test12 test13 test14 test15 test16

# Run tests using the student's shell program
test01:
	$(DRIVER) -t trace01.txt -s $(TSH) -a $(TSHARGS) > $@
test02:
	$(DRIVER) -t trace02.txt -s $(TSH) -a $(TSHARGS) > $@
test03:
	$(DRIVER) -t trace03.txt -s $(TSH) -a $(TSHARGS) > $@
test04:
	$(DRIVER) -t trace04.txt -s $(TSH) -a $(TSHARGS) > $@
test05:
	$(DRIVER) -t trace05.txt -s $(TSH) -a $(TSHARGS) > $@
test06:
	$(DRIVER) -t trace06.txt -s $(TSH) -a $(TSHARGS) > $@
test07:
	$(DRIVER) -t trace07.txt -s $(TSH) -a $(TSHARGS) > $@
test08:
	$(DRIVER) -t trace08.txt -s $(TSH) -a $(TSHARGS) > $@
test09:
	$(DRIVER) -t trace09.txt -s $(TSH) -a $(TSHARGS) > $@
test10:
	$(DRIVER) -t trace10.txt -s $(TSH) -a $(TSHARGS) > $@
test11:
	$(DRIVER) -t trace11.txt -s $(TSH) -a $(TSHARGS) > $@
test12:
	$(DRIVER) -t trace12.txt -s $(TSH) -a $(TSHARGS) > $@
test13:
	$(DRIVER) -t trace13.txt -s $(TSH) -a $(TSHARGS) > $@
test14:
	$(DRIVER) -t trace14.txt -s $(TSH) -a $(TSHARGS) > $@
test15:
	$(DRIVER) -t trace15.txt -s $(TSH) -a $(TSHARGS) > $@
test16:
	$(DRIVER) -t trace16.txt -s $(TSH) -a $(TSHARGS) > $@

rtest: rtest01 rtest02 rtest03 rtest04 rtest05 rtest06 rtest07 rtest08 rtest09 rtest10 rtest11 rtest12 rtest13 rtest14 rtest15 rtest16

# Run the tests using the reference shell program
rtest01:
	$(DRIVER) -t trace01.txt -s $(TSHREF) -a $(TSHARGS) > test01
rtest02:
	$(DRIVER) -t trace02.txt -s $(TSHREF) -a $(TSHARGS) > test02
rtest03:
	$(DRIVER) -t trace03.txt -s $(TSHREF) -a $(TSHARGS) > test03
rtest04:
	$(DRIVER) -t trace04.txt -s $(TSHREF) -a $(TSHARGS) > test04
rtest05:
	$(DRIVER) -t trace05.txt -s $(TSHREF) -a $(TSHARGS) > test05
rtest06:
	$(DRIVER) -t trace06.txt -s $(TSHREF) -a $(TSHARGS) > test06
rtest07:
	$(DRIVER) -t trace07.txt -s $(TSHREF) -a $(TSHARGS) > test07
rtest08:
	$(DRIVER) -t trace08.txt -s $(TSHREF) -a $(TSHARGS) > test08
rtest09:
	$(DRIVER) -t trace09.txt -s $(TSHREF) -a $(TSHARGS) > test09
rtest10:
	$(DRIVER) -t trace10.txt -s $(TSHREF) -a $(TSHARGS) > test10
rtest11:
	$(DRIVER) -t trace11.txt -s $(TSHREF) -a $(TSHARGS) > test11
rtest12:
	$(DRIVER) -t trace12.txt -s $(TSHREF) -a $(TSHARGS) > test12
rtest13:
	$(DRIVER) -t trace13.txt -s $(TSHREF) -a $(TSHARGS) > test13
rtest14:
	$(DRIVER) -t trace14.txt -s $(TSHREF) -a $(TSHARGS) > test14
rtest15:
	$(DRIVER) -t trace15.txt -s $(TSHREF) -a $(TSHARGS) > test15
rtest16:
	$(DRIVER) -t trace16.txt -s $(TSHREF) -a $(TSHARGS) > test16


# clean up
clean:
	rm -f $(FILES) *.o *~
	rm -f test*


