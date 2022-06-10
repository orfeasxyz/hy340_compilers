#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include <map>
#include <string>

#define AVM_STACKSIZE		4096
#define AVM_TABLE_HASHSIZE	211

enum avm_memcell_e {
	undef_m,
	number_m,
	string_m,
	bool_m,
	table_m,
	userfunc_m,
	libfunc_m,
	nil_m
};

struct avm_table;
struct avm_memcell {
	avm_memcell_e type;
	union {
		double		numVal;
		char*		strVal;
		bool		boolVal;
		avm_table*	tableVal;
		unsigned	funcVal;
		char*		libFuncVal;
	} data;
};

extern avm_memcell stack[AVM_STACKSIZE];
void avm_stackinit(void);

using strIndexedTable = std::map<std::string, avm_memcell*>;
using numIndexedTable = std::map<unsigned, avm_memcell*>;

struct avm_table {
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
