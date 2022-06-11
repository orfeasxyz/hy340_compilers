CC=g++
BASE_DIR=../
EXE_NAME=$(BASE_DIR)/vm.exe
IDIR=$(BASE_DIR)/include/
CDFLAGS=-I $(IDIR) -DDEBUG -Wall -g
CFLAGS=-I $(IDIR) -Wall -g
OBJ=vm.cpp parser.cpp environment.cpp dispatcher.cpp

all: $(OBJ)
	$(CC) $(CDFLAGS) $(OBJ) -o $(EXE_NAME)

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c *.exe *.output
