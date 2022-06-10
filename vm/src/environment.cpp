#include  "environment.h"
#include <cstring>

// Const values tables
std::vector<double>			numConsts;
std::vector<std::string>	strConsts;
std::vector<userfunc>		userFuncs;
std::vector<std::string>	libFuncs;
std::vector<instruction>	instructions;

// 3 general purpose registes, 1 retval register, stack pointer, base pointer
avm_memcell	ax;
avm_memcell	bx;
avm_memcell	cx;
avm_memcell	retval;
unsigned	sp;
unsigned	bp;

avm_memcell stack[AVM_STACKSIZE];

// ----- stack procedures -----
void avm_stackinit(void) {
	memset(stack, 0, sizeof(stack));
	for (auto &cell : stack) {
		cell.type = undef_m;
	}
}


