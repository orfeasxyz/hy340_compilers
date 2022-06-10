#include "bin_parser.h"
#include <cassert>

#ifdef DEBUG
#	define DPRINTF(...)	fprintf(stderr, ...)
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

	return 0;
}
