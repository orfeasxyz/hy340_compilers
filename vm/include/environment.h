#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <vector>
#include <map>
#include <string>

#define WARNING_BUFF_SIZE   512
#define AVM_STACK_SIZE		4096
#define AVM_STACKENV_SIZE	4
#define AVM_NUMACTS_OFFSET  4
#define AVM_SAVEDPC_OFFSET  3
#define AVM_SAVEDSP_OFFSET  2
#define AVM_SAVEDBP_OFFSET  1

enum vmopcode_e {
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
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
};

enum vmarg_e {
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userFunc_a,
    libFunc_a,
    retval_a,
};

struct vmarg {
    vmarg_e type;
    unsigned val;
};

struct instruction {
    vmopcode_e	op;
    vmarg		result;
    vmarg		arg1;
    vmarg		arg2;
    unsigned	srcLine;
};

struct userFunc {
    unsigned address;
    unsigned localSize;
	std::string id;
};

enum avm_memcell_e {
	number_m,
	string_m,
	bool_m,
    table_m,
	userFunc_m,
	libFunc_m,
	nil_m,
    undef_m
};

struct avm_table;
struct avm_memcell {
	avm_memcell_e type;
	union { 
		double		numVal;
		char*		strVal;
		bool		boolVal;
		avm_table*	tableVal;
		unsigned	userFuncVal;
		char*		libFuncVal;
	} data;
};

struct avm_table {
	using strIndexedTable = std::map<std::string, avm_memcell*>;
	using numIndexedTable = std::map<unsigned, avm_memcell*>;
	unsigned		refCounter;
	strIndexedTable	strIndexed;
	numIndexedTable	numIndexed;
};

// Const values tables
extern std::vector<double>		numConsts;
extern std::vector<std::string>	strConsts;
extern std::vector<userFunc>	userFuncs;
extern std::vector<std::string>	libFuncs;
extern std::vector<instruction>	instructions;

// Total number of globals
extern unsigned     globalsCount;

// 3 general purpose registes, 1 retval register, stack pointer, base pointer
extern avm_memcell	ax;
extern avm_memcell	bx;
extern avm_memcell	cx;
extern avm_memcell	retval;
extern unsigned		sp;
extern unsigned		bp;
extern unsigned     pc;
extern bool         executionFinished;
extern unsigned     currLine;
extern unsigned     codeSize;
extern unsigned     totalActuals;

extern avm_memcell	stack[AVM_STACK_SIZE];

const char* avm_type2str        (unsigned i);
void        avm_stackinit       (void);
void        avm_memcellclear    (avm_memcell *m);
avm_memcell*avm_translate_op    (vmarg *arg, avm_memcell *reg);
void        avm_warning         (const char *format, ...);
void        avm_error           (const char *format, ...);
void        avm_assign          (avm_memcell *lv, avm_memcell *rv);
void        avm_decsp           (void);
void        avm_pushenv         (unsigned val);
void        avm_callsaveenv     (void);
void        avm_calllibfunc     (char *id);
userFunc    avm_getfuncinfo     (unsigned addr);
unsigned    avm_getenvval       (unsigned i);
char*       avm_tostring        (avm_memcell* m);
bool        avm_tobool          (avm_memcell* m);
avm_table*	avm_tablenew        (void);
avm_memcell*avm_tablegetelem    (avm_table *table, avm_memcell* key);
void		avm_tablesetelem    (avm_table *table, avm_memcell* key, avm_memcell* value);
void		avm_tablerefinc     (avm_table *table);
void		avm_tablerefdec     (avm_table *table);
void		avm_tabledestroy    (avm_table *table);

#endif // ENVIRONMENT_H
