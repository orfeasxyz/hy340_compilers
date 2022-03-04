CC=gcc
BASE_DIR=../
IDIR=$(BASE_DIR)/include/
CFLAGS=-I $(IDIR) -DDEBUG
OBJ=lex.yy.c al.c

all: lex

lex: al.c lex.l $(IDIR)/lex.h
<<<<<<< HEAD
	flex lex.l
	$(CC) $(CFLAGS) $(OBJ) -o $(BASE_DIR)/alpha.exe
=======
	lex lex.l
	$(CC) $(CFLAGS) $(OBJ) -o $(BASE_DIR)/alpha.out
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c
