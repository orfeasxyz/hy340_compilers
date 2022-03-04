CC=gcc
BASEDIR=$(HOME)/CSD/340/hy340_compilers
IDIR=$(BASEDIR)/include/
CFLAGS=-I $(IDIR) -DDEBUG
OBJ=lex.yy.c al.c

all: lex

lex: al.c lex.l $(IDIR)/lex.h
	lex lex.l
	$(CC) $(CFLAGS) $(OBJ) -o $(BASEDIR)/alpha.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c
