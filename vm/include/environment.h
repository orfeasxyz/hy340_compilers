#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "structs.h" // avm_memcell, avm_table

#define AVM_STACKSIZE		4096
#define AVM_STACKENV_SIZE	4

// Const values tables
extern std::vector<double>		numConsts;
extern std::vector<std::string>	strConsts;
extern std::vector<userfunc>	userFuncs;
extern std::vector<std::string>	libFuncs;
extern std::vector<instruction>	instructions;

// 3 general purpose registes, 1 retval register, stack pointer, base pointer
extern avm_memcell	ax;
extern avm_memcell	bx;
extern avm_memcell	cx;
extern avm_memcell	retval;
extern unsigned		sp;
extern unsigned		bp;

extern avm_memcell	stack[AVM_STACKSIZE];

void avm_stackinit(void);

#endif // ENVIRONMENT_H
