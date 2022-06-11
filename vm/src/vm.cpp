#include "../include/parser.h"
#include "../include/dispatcher.h"
#include "../include/environment.h"
#include <cassert>

#ifdef DEBUG
#	define DPRINTF(...)	fprintf(stderr, __VA_ARGS__)
#else
#	define DPRINTF(...)
#endif

/*
 * std::vector<userfunc>		userFuncs;
 * std::vector<instruction>		instructions;
 * std::vector<std::string>		libFuncs;
 * std::vector<double>			numConsts;
 * std::vector<std::string>		strConsts;
 */
int main(int argc, char **argv) {
	assert(argc == 2);
	parseBinary(argv[1]);
	
	// Init
	sp = AVM_STACK_SIZE-2;
	bp = sp;
	pc = 0;
	executionFinished = false;
	codeSize = instructions.size();
	DPRINTF("codeSize = %u\n", codeSize);
	totalActuals = 0;
	avm_stackinit();
	while (!executionFinished) {
		DPRINTF("executionFinished = %s\n", executionFinished ? "True" : "False");
		DPRINTF("pc = %u\n", pc);
		DPRINTF("sp = %u\n", sp);
		DPRINTF("bp = %u\n", bp);
		DPRINTF("retval = %lf\n", retval.data.numVal);
		execute_cycle();
	}

	return 0;
}
