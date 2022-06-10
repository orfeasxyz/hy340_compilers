#include "structs.h"
#include <cassert>
#include <cstring>


// ----- avm_table procedures -----
avm_table* avm_tablenew (void) {
	avm_table *res = new avm_table;
	res->refCounter = 0;
	return res;
}

avm_memcell* avm_tablegetelem (avm_table *table, avm_memcell *key) {
	avm_memcell *res = NULL;
	assert(table);
	assert(key);
	switch (key->type) {
		case string_m:
			// TODO error checking if key is not found
			res = table->strIndexed[key->data.strVal];
			break;
		case number_m:
			// TODO error checking
			res = table->numIndexed[static_cast<unsigned>(key->data.numVal)];
			break;
		default:
			;
			// TODO error illegal key value error
	}
	assert(res); // res can't be NULL if errors are handled properly
	return res;
}

void avm_tablesetelem (avm_table *table, avm_memcell *key, avm_memcell *value) {
	assert(table);
	assert(key);
	assert(value);
	switch (key->type) {
		case string_m:
			// TODO error checking if key is not found table->strIndexed[key->strVal] = value;
			break;
		case number_m:
			// TODO error checking
			table->numIndexed[static_cast<unsigned>(key->data.numVal)] = value;
			break;
		default:
			;
			// TODO error illegal key value error
	}
}

void avm_tableincref (avm_table *table) {
	assert(table);
	++table->refCounter;
}

void avm_tabledecref (avm_table *table) {
	assert(table);
	assert(table->refCounter > 0);

	if (--table->refCounter == 0) {
		avm_tabledestroy(table);
	}
}

void avm_tabledestroy (avm_table *table) {
	assert(table);
	for (auto &e : table->strIndexed) {
		if (e.second->type == table_m) {
			avm_tabledecref(e.second->data.tableVal);
		}
	}
	for (auto &e : table->numIndexed) {
		if (e.second->type == table_m) {
			avm_tabledecref(e.second->data.tableVal);
		}
	}
	delete table;
}
