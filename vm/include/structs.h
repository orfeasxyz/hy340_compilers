#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include <map>
#include <string>

enum vmopcode_e {
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

struct userfunc {
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

avm_table*		avm_tablenew (void);
avm_memcell*	avm_tablegetelem (avm_table *table, avm_memcell* key);
void			avm_tablesetelem (avm_table *table, avm_memcell* key, avm_memcell* value);
void			avm_tableincref (avm_table *table);
void			avm_tabledecref (avm_table *table);
void			avm_tabledestroy (avm_table *table);

#endif	// STRUCTS_H
