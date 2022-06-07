CC=gcc
BASE_DIR=../
IDIR=$(BASE_DIR)/include/
CFLAGS=-I $(IDIR) -DDEBUG -Wall -g
OBJ=lex.yy.c parser.c rule_handler.c symtable.c stack.c structs.c target.c binary.c

all: parser lex
	$(CC) $(CFLAGS) $(OBJ) -o $(BASE_DIR)/alpha.exe

parser:
	bison --yacc --defines parser.y --output=parser.c
	mv parser.h $(IDIR)

lex: al.c lex.l $(IDIR)/lex.h parser
	flex lex.l

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c *.exe *.output
