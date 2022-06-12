#include  "../include/environment.h"
#include "../include/dispatcher.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

// Const values tables
std::vector<double>			numConsts;
std::vector<std::string>	strConsts;
std::vector<userFunc>		userFuncs;
std::vector<std::string>	libFuncs;
std::vector<instruction>	instructions;

// Total number of globals
unsigned    globalsCount;
// 3 general purpose registes, 1 retval register, stack pointer, base pointer
avm_memcell	ax;
avm_memcell	bx;
avm_memcell	cx;
avm_memcell	retval;
unsigned	sp;
unsigned	bp;
unsigned    pc;
bool        executionFinished;
unsigned    currLine;
unsigned    codeSize;
unsigned 	totalActuals;

avm_memcell stack[AVM_STACK_SIZE];

// ----- Stack procedures -----
void avm_stackinit(void) {
	memset(stack, 0, sizeof(stack));
	for (auto &cell : stack) {
		cell.type = undef_m;
	}
}

typedef void (*memclear_func_t)(avm_memcell*);

static void memclear_string (avm_memcell *m) {
    assert(m->data.strVal);
    free(m->data.strVal);
}

static void memclear_table (avm_memcell *m) {
    assert(m->data.tableVal);
    avm_tablerefdec(m->data.tableVal);
}

static memclear_func_t memclearFuncs[] = {
    NULL,
    memclear_string,
    NULL,
    memclear_table,
    NULL,
    NULL,
    NULL,
    NULL
};

void avm_memcellclear (avm_memcell *m) {
    if (m->type == undef_m) {
        return;
    }
    memclear_func_t f = memclearFuncs[m->type];
    if (f) {
        f(m);
    }
    m->type = undef_m;
}

// ----- Translate operands -----
avm_memcell* avm_translate_op (vmarg *arg, avm_memcell *reg) {
	switch (arg->type) {
		case global_a:	return &stack[AVM_STACK_SIZE - 1 - arg->val];
		case local_a:	return &stack[bp - arg->val];
		case formal_a:	return &stack[bp + AVM_STACKENV_SIZE + 1 + arg->val];
		case retval_a:	return &retval;
		case number_a:	{
			reg->type = number_m;
			reg->data.numVal = numConsts.at(arg->val);
			return reg;
		}
		case string_a:	{
			reg->type = string_m;
			reg->data.strVal = strdup(strConsts.at(arg->val).c_str());
			return reg;
		}
		case bool_a:	{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}
		case nil_a:		{
			reg->type = nil_m;
			return reg;
		}
		case userFunc_a:	{
			reg->type = userFunc_m;
			reg->data.userFuncVal = userFuncs[arg->val].address;
			return reg;
		}
		case libFunc_a:	{
			reg->type = libFunc_m;
			reg->data.libFuncVal = strdup(libFuncs.at(arg->val).c_str());
			return reg;
		}
		default:		assert(0);
	}
	return NULL;
}


// ----- Runtime messages -----
void avm_warning(const char *format, ...) {
    static char buffer[WARNING_BUFF_SIZE] = {0};
    sprintf(buffer, "[Warning] %u : %s", pc, format);
    va_list args;
    va_start(args,format);
    vfprintf(stderr, buffer, args); 
    va_end(args);
}

void avm_error(const char *format, ...) {
    static char buffer[WARNING_BUFF_SIZE] = {0};
    sprintf(buffer, "[Error] %u : %s", pc, format);
    va_list args;
    va_start(args,format);
    vfprintf(stderr, buffer, args); 
    va_end(args);
    assert(0);
    exit(1);
}

// ----- AVM environment helper functions -----
void avm_assign (avm_memcell *lv, avm_memcell *rv) {
    if (lv == rv            and
        lv->type == table_m and
        rv->type == table_m and
        lv->data.tableVal == rv->data.tableVal) {
            return;
    }

    if (rv->type == undef_m) {
        avm_warning("Assigning from 'undefined' variable\n");
    }

    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if (lv->type == table_m) {
        avm_tablerefinc(lv->data.tableVal);
    }
}

void avm_decsp (void) {
    if (sp <= 0) {
        avm_error("Stack overflow\n"); // DOESN'T RETURN
    }
    --sp;
}

void avm_pushenv (unsigned val) {
    stack[sp].type          = number_m;
    stack[sp].data.numVal   = val;
    avm_decsp();
}

void avm_callsaveenv (void) {
    avm_pushenv(totalActuals);
    avm_pushenv(pc+1);
    avm_pushenv(sp+totalActuals+2);
    avm_pushenv(bp);
}

userFunc avm_getfuncinfo (unsigned addr) {
    userFunc dummy;
    for (auto & uF : userFuncs) {
        if (uF.address == addr) {
            return uF;
        }
    }
    avm_error("No function in address %u\n", addr);
    return dummy;
}

unsigned avm_getenvval(unsigned int i) {
	assert(stack[i].type == number_m);
	unsigned val = static_cast<unsigned>(stack[i].data.numVal);
	assert(stack[i].data.numVal == static_cast<double>(val));
	return val;
}

unsigned avm_totalactuals (void) {
    return avm_getenvval(bp + AVM_NUMACTS_OFFSET);
}

avm_memcell* avm_getactual (unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[bp + AVM_STACKENV_SIZE + 1 + i];
}

typedef void (*library_func_t) (void);

void libFunc_print (void) {
    int n = avm_totalactuals();
    for (int i = n - 1; i >= 0; --i) {
        char *s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
    retval.type = bool_m;
    retval.data.boolVal = true;

    fflush(stdout);
}

void libFunc_totalarguments (void) {
    unsigned p_bp = avm_getenvval(bp + AVM_SAVEDBP_OFFSET);
    avm_memcellclear(&retval);

    if (!)
}

// TODO register more libfuncs ^-^
std::map<std::string, library_func_t> libFuncsMap = {
    {"print", libFunc_print}
};

library_func_t avm_getlibraryfunc (std::string id) {
    if (!libFuncsMap.count(id)) {
        return NULL;
    }
    return libFuncsMap[id];
}

void avm_calllibfunc(char *id) {
    std::string strId(id);
    library_func_t f;
    if (!(f = avm_getlibraryfunc(strId))) {
        avm_error("Unsupported lib function '%s' called\n", id);
    }
    bp = sp;
    totalActuals = 0;
    f(); // TODO implement libfuncs
    if (!executionFinished) {
        execute_funcexit(NULL);
    }
}

// ----- avm_table procedures -----
avm_table* avm_tablenew (void) {
	avm_table *res = new avm_table;
	res->refCounter = 0;
	return res;
}

void avm_tabledestroy (avm_table *table) {
	assert(table);
	for (auto &e : table->strIndexed) {
		if (e.second->type == table_m) {
			avm_tablerefdec(e.second->data.tableVal);
		}
	}
	for (auto &e : table->numIndexed) {
		if (e.second->type == table_m) {
			avm_tablerefdec(e.second->data.tableVal);
		}
	}
	delete table;
}

void avm_tablerefinc (avm_table *table) {
	assert(table);
	++table->refCounter;
}

void avm_tablerefdec (avm_table *table) {
	assert(table);
	assert(table->refCounter > 0);

	if (--table->refCounter == 0) {
		avm_tabledestroy(table);
	}
}

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *value) {
    avm_memcell *res;
    switch (index->type) {
        case number_m: {
            unsigned numIndex = static_cast<unsigned>(index->data.numVal);
            res = (avm_memcell*)malloc(sizeof(avm_memcell));
            memcpy(res, value, sizeof(avm_memcell));
            table->numIndexed[numIndex] = res;
            break;
        }
        case string_m: {
            std::string strIndex(index->data.strVal);
            res = (avm_memcell*)malloc(sizeof(avm_memcell));
            memcpy(res, value, sizeof(avm_memcell));
            table->strIndexed[strIndex] = res;
            break;
        }
        default:
            avm_error("Illegal key type\n");
    }
}

// TODO Must check behaviour when the key is not found
avm_memcell* avm_tablegetelem(avm_table *table, avm_memcell *index) {
    avm_memcell *res;
    switch (index->type) {
        case number_m: {
            // Rounding number
            unsigned numIndex = static_cast<unsigned>(index->data.numVal);
            if (!table->numIndexed.count(numIndex)) {
                res = (avm_memcell*)malloc(sizeof(avm_memcell));
                res->type = nil_m;
                return res;
            }
            return table->numIndexed[numIndex];
            break;
        }
        case string_m: {
            std::string strIndex(index->data.strVal);
            if (!table->strIndexed.count(strIndex)) {
                res = (avm_memcell*)malloc(sizeof(avm_memcell));
                res->type = nil_m;
                return res;
            }
            return table->strIndexed[strIndex];
            break;
        }
        default:
            // Any other key type should be prohibited
            assert(0);
    }
    return NULL;
}

// ----- String conversion dispatcher -----
#define TOSTRING_LEN	128

typedef char* (*tostring_func_t)(avm_memcell*);

static char* number_tostring (avm_memcell *m) {
	char *str = (char*)malloc(32);
	sprintf(str, "%lf", m->data.numVal);
	return str;
}

static char* string_tostring (avm_memcell *m) {
	return strdup(m->data.strVal);
}

static char* bool_tostring (avm_memcell *m) {
	return strdup(m->data.boolVal ? "True" : "False");
}

static char* table_tostring (avm_memcell *m) {
	std::string str;
	char intBuf[TOSTRING_LEN];
	str += "[";
	size_t n =  m->data.tableVal->numIndexed.size() + 
                m->data.tableVal->strIndexed.size();
	size_t i = 0;
	for (const auto &e : m->data.tableVal->numIndexed) {
		str += "{";
		sprintf(intBuf, "%u", e.first);
		str += intBuf;
		str += ", ";
		str += avm_tostring(e.second);
		str += "}";
		if (i++ < n-1) {
			str += ",";
		}
	}
	for (const auto &e : m->data.tableVal->strIndexed) {
		str += "{";
		str += e.first;
		str += ", ";
		str += avm_tostring(e.second);
		str += "}";
		if (i++ < n-1) {
			str += ",";
		}
	}
	str += "]";
	return strdup(str.c_str());
}

static char* userFunc_tostring (avm_memcell *m) {
    char *str = (char*)malloc(TOSTRING_LEN);
	sprintf(str, "%u", m->data.userFuncVal);
	return str;
}

static char* libFunc_tostring (avm_memcell *m) {
    return strdup(m->data.libFuncVal);
}

static char* nil_tostring (avm_memcell*) {
	return strdup("Nil");
}
static char* undef_tostring (avm_memcell*) {
    return strdup("Undefined");
}

static tostring_func_t tostringFuncs[] = {
	 number_tostring,
	 string_tostring,
	 bool_tostring,
	 table_tostring,
	 userFunc_tostring,
	 libFunc_tostring,
	 nil_tostring,
	 undef_tostring
};

char* avm_tostring(avm_memcell* m){
	assert(m->type >= 0 and m->type <= undef_m);
	return tostringFuncs[m->type](m);
}

// ----- Bool conversion dispatcher -----
typedef bool (*tobool_func_t)(avm_memcell*);

static bool number_tobool  (avm_memcell *m) {
    return m->data.numVal != 0.0;
}

static bool string_tobool  (avm_memcell *m) {
    return m->data.strVal[0] != 0;
}

static bool bool_tobool    (avm_memcell *m) {
    return m->data.boolVal;
}

static bool table_tobool   (avm_memcell *m) {
    return true;
    // return  m->data.tableVal->numIndexed.size() +
    //         m->data.tableVal->strIndexed.size() > 0;
}

static bool userFunc_tobool(avm_memcell *m) {
    return true;
}

static bool libFunc_tobool (avm_memcell *m) {
    return true;
}

static bool nil_tobool (avm_memcell *m) {
    return false;
}

static bool undef_tobool   (avm_memcell *m) {
    avm_error("Cannot convert 'undef' to bool\n");
    return false;
}

static tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userFunc_tobool,
    libFunc_tobool,
    nil_tobool,
    undef_tobool
};

bool avm_tobool(avm_memcell* m){
	assert(m->type >= 0 and m->type <= undef_m);
	return toboolFuncs[m->type](m);
}