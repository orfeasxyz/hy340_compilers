#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "structs.h" // avm_memcell, avm_table

#define WARNING_BUFF_SIZE   512
#define AVM_STACKSIZE		4096
#define AVM_STACKENV_SIZE	4
#define AVM_NUMACTS_OFFSET  4
#define AVM_SAVEDSP_OFFSET  3
#define AVM_SAVEDPC_OFFSET  2
#define AVM_SAVEDBP_OFFSET  1

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
extern unsigned    pc;
extern bool        executionFinished;
extern unsigned    currLine;
extern unsigned    codeSize;
extern unsigned    totalActuals;

extern avm_memcell	stack[AVM_STACKSIZE];

void        avm_stackinit       (void);
void        avm_memcellclear    (avm_memcell *m);
void        avm_warning         (const char *format, ...);
void        avm_error           (const char *format, ...);
void        avm_assign          (avm_memcell *lv, avm_memcell *rv);
void        avm_decsp           (void);
void        avm_pushenv         (unsigned val);
void        avm_callsaveenv     (void);
userfunc    avm_getfuncinfo     (unsigned addr);
unsigned    avm_getenvval       (unsigned i);
char*       avm_tostring        (avm_memcell* m);
bool        avm_tobool          (avm_memcell* m);

#endif // ENVIRONMENT_H
