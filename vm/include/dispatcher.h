#include "../include/environment.h"
#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v

void execute_cycle          (void);          
void execute_assign         (instruction*);
void execute_add            (instruction*);
void execute_sub            (instruction*);
void execute_mul            (instruction*);
void execute_div            (instruction*);
void execute_mod            (instruction*);
void execute_arithmetic     (instruction*);
void execute_jump           (instruction*);
void execute_jeq            (instruction*);
void execute_jne            (instruction*);
void execute_jle            (instruction*);
void execute_jge            (instruction*);
void execute_jlt            (instruction*);
void execute_jgt            (instruction*);
void execute_comparison     (instruction*);
void execute_call           (instruction*);
void execute_pusharg        (instruction*);
void execute_funcenter      (instruction*);
void execute_funcexit       (instruction*);
void execute_newtable       (instruction*);
void execute_tablegetelem   (instruction*);
void execute_tablesetelem   (instruction*);
void execute_nop            (instruction*);