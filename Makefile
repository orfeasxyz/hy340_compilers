BIN_DIR="$(shell pwd)"
CFLAGS=-Wall -g -DDEBUG

.PHONY: all clean

all:
	$(MAKE) -C compiler/src/ BIN_DIR="$(shell pwd)" CFLAGS="$(CFLAGS)"
	$(MAKE) -C vm/src/ BIN_DIR="$(shell pwd)" CFLAGS="$(CFLAGS)"

clean:
	rm -f *.exe *.ascb
	$(MAKE) -C compiler/src/ clean
	$(MAKE) -C vm/src/ clean