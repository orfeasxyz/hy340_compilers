CC=gcc
BASE_DIR=../
IDIR=$(BASE_DIR)/include/
CFLAGS=-I $(IDIR) -DDEBUG -Wall
OBJ=lex.yy.c al.c

all: lex

lex: al.c lex.l $(IDIR)/lex.h
	flex lex.l
	$(CC) $(CFLAGS) $(OBJ) -o $(BASE_DIR)/alpha.out

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c *.exe
