CC=g++
BASE_DIR=../
IDIR=$(BASE_DIR)/include/
OBJ=vm.cpp parser.cpp environment.cpp dispatcher.cpp

.PHONY: all clean

all: $(OBJ)
	$(CC) -I $(IDIR) $(CFLAGS) $(OBJ) -o $(BIN_DIR)/vm.exe

clean:
	rm -rf *.o *.out *.yy.c *.exe *.output
