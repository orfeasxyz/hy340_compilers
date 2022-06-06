#ifndef _TARGET_H_
#define _TARGET_H_

#include "structs.h"

typedef enum vmopcode {
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jump_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,
    pusharg_v,
    funcenter_v,
    funcexit_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v
} vmopcode;

typedef enum vmarg_t {
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a,
} vmarg_t;

typedef struct vmarg {
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction {
    vmopcode op;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
} instruction;

extern instruction* instructions;
extern unsigned total_instructions;
extern unsigned currInstruction;

#define EXPAND_INSTRUCTION_SIZE 1024
#define CURR_INSTRUCTION_SIZE (total_instructions * sizeof(instruction))
#define NEW_INSTRUCTION_SIZE \
    (EXPAND_INSTRUCTION_SIZE * sizeof(instruction) + CURR_INSTRUCTION_SIZE)

void expand_instruction();
void emit_instruction(instruction);

typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    char* id;
} userfunc;

typedef struct incomplete_jump {
    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump* next;
} incomplete_jump;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);

extern incomplete_jump* ij_head;
extern unsigned ij_total;

extern double* numConsts;
extern unsigned totalNumConsts;
extern unsigned currNumConsts;
#define EXPAND_NUMCONST_SIZE 1024
#define CURR_NUMCONST_SIZE (totalNumConsts * sizeof(double))
#define NEW_NUMCONST_SIZE \
    (EXPAND_NUMCONST_SIZE * sizeof(double) + CURR_NUMCONST_SIZE)

void expand_numconst();

extern char** strConsts;
extern unsigned totalStrConsts;
extern unsigned currStrConsts;
#define EXPAND_STRCONST_SIZE 1024
#define CURR_STRCONST_SIZE (totalStrConsts * sizeof(char*))
#define NEW_STRCONST_SIZE \
    (EXPAND_STRCONST_SIZE * sizeof(char*) + CURR_STRCONST_SIZE)

void expand_strconst();

extern char** nameLibfuncs;
extern unsigned totalNameLibfuncs;
extern unsigned currNameLibfuncs;
#define EXPAND_NAMELIBFUNCS_SIZE 1024
#define CURR_NAMELIBFUNCS_SIZE (totalNameLibfuncs * sizeof(char*))
#define NEW_NAMELIBFUNCS_SIZE \
    (EXPAND_NAMELIBFUNCS_SIZE * sizeof(char*) + CURR_NAMELIBFUNCS_SIZE)

void expand_namelibfuncs();

extern userfunc* userFuncs;
extern unsigned totalUserFuncs;
extern unsigned currUserFuncs;
#define EXPAND_USERFUNCS_SIZE 1024
#define CURR_USERFUNCS_SIZE (totalUserFuncs * sizeof(userfunc))
#define NEW_USERFUNCS_SIZE \
    (EXPAND_USERFUNCS_SIZE * sizeof(userfunc) + CURR_USERFUNCS_SIZE)

void expand_userfuncs();

unsigned consts_newstring(char*);
unsigned consts_newnumber(double);
unsigned libfuncs_newused(char*);
unsigned userfuncs_newfunc(SymbolTableEntry*);
void make_operand(Expr*, vmarg*);
unsigned nextInstructionLabel(void);

void generate_ADD(quad*);
void generate_SUB(quad*);
void generate_MUL(quad*);
void generate_DIV(quad*);
void generate_MOD(quad*);
void generate_NEWTABLE(quad*);
void generate_TABLEGETELEM(quad*);
void generate_TABLESETELEM(quad*);
void generate_ASSIGN(quad*);
void generate_NOP(quad*);
void generate_JUMP(quad*);
void generate_IF_EQ(quad*);
void generate_IF_NOTEQ(quad*);
void generate_IF_GREATER(quad*);
void generate_IF_GREATEREQ(quad*);
void generate_IF_LESS(quad*);
void generate_IF_LESSEQ(quad*);
void generate_NOT(quad*);
void generate_OR(quad*);
void generate_AND(quad*);
void generate_PARAM(quad*);
void generate_CALL(quad*);
void generate_GETRETVAL(quad*);
void generate_FUNCSTART(quad*);
void generate_RETURN(quad*);
void generate_FUNCEND(quad*);

typedef void (*generate_func_t)(quad*);


void generate_all(void);

#endif  // _TARGET_H_
