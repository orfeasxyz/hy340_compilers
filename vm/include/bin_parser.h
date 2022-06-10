#ifndef BIN_PARSER_H
#define BIN_PARSER_C
#include <vector>
#include <string>

typedef enum vmopcode_e {
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
    funcexit_v, newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v
} vmopcode_e;

typedef enum vmarg_e {
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
} vmarg_e;

typedef struct vmarg {
    vmarg_e type;
    unsigned val;
} vmarg_t;

typedef struct instruction {
    vmopcode_e op;
    vmarg_t result;
    vmarg_t arg1;
    vmarg_t arg2;
    unsigned srcLine;
} instruction;

typedef struct userfunc {
    unsigned address;
    unsigned localSize;
	std::string id;
} userfunc;

extern std::vector<std::string>	strConsts;
extern std::vector<double>		numConsts;
extern std::vector<userfunc>	userFuncs;
extern std::vector<std::string>	libFuncs;
extern std::vector<instruction>	instructions;

 void parseBinary(char *filename);

#endif	// BIN_PARSER_H
