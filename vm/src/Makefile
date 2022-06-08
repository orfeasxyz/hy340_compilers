CC=g++
BASE_DIR=../
EXE_NAME=$(BASE_DIR)/vm.exe
IDIR=$(BASE_DIR)/include/
CFLAGS=-I $(IDIR) -DDEBUG -Wall -g
OBJ=vm.cpp

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE_NAME)

.PHONY: clean
clean:
	rm -rf *.o *.out *.yy.c *.exe *.output
