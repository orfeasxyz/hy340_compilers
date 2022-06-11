#include "../include/environment.h"
#include "../include/structs.h"
#include "../include/translate.h"
#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v

extern void execute_assign      (instruction&);
extern void execute_add         (instruction&);
extern void execute_sub         (instruction&);
extern void execute_mul         (instruction&);
extern void execute_div         (instruction&);
extern void execute_mod         (instruction&);
extern void execute_arithmetic  (instruction&);
extern void execute_jeq         (instruction&);
extern void execute_jne         (instruction&);
extern void execute_jle         (instruction&);
extern void execute_jge         (instruction&);
extern void execute_jlt         (instruction&);
extern void execute_jgt         (instruction&);
extern void execute_comparison  (instruction&);
extern void execute_call        (instruction&);
extern void execute_pusharg     (instruction&);
extern void execute_funcenter   (instruction&);
extern void execute_funcexit    (instruction&);
extern void execute_newtable    (instruction&);
extern void execute_tablegetelem(instruction&);
extern void execute_tablesetelem(instruction&);
extern void execute_nop         (instruction&);