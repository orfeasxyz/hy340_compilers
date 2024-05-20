CC=gcc
BASE_DIR=../
IDIR=$(BASE_DIR)/include/
OBJ=lex.yy.c parser.c rule_handler.c symtable.c stack.c structs.c target.c binary.c

.PHONY: all clean

all: parser lex
	$(CC) -I $(IDIR) $(CFLAGS) $(OBJ) -o $(BIN_DIR)/alpha.exe

parser:
	bison --yacc --defines parser.y --output=parser.c
	mv parser.h $(IDIR)

lex: al.c lex.l $(IDIR)/lex.h parser
	flex lex.l

clean:
	rm -rf *.o *.out *.yy.c *.exe *.output parser.c
