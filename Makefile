
.PHONY: all clean

all:
	$(MAKE) -C compiler/ BIN_DIR="$(shell pwd)/bin"
	$(MAKE) -C vm/ BIN_DIR="$(shell pwd)/bin"

clean:
	$(MAKE) -C compiler/ clean
	$(MAKE) -C compiler/ clean
	rm -f bin/*.exe
