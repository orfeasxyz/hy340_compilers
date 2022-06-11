#include  "../include/environment.h"
#include <string.h>
#include <cstdio>
#include <cstring>
#include <cassert>

// Const values tables
std::vector<double>			numConsts;
std::vector<std::string>	strConsts;
std::vector<userfunc>		userFuncs;
std::vector<std::string>	libFuncs;
std::vector<instruction>	instructions;

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

avm_memcell stack[AVM_STACKSIZE];

// ----- stack procedures -----
void avm_stackinit(void) {
	memset(stack, 0, sizeof(stack));
	for (auto &cell : stack) {
		cell.type = undef_m;
	}
}

typedef void (*memclear_func_t)(avm_memcell*);

static void memclear_string (avm_memcell *m) {
    assert(m->data.strVal);
    free(m->data.strVal); // TODO SUSSY
}

static void memclear_table (avm_memcell *m) {
    assert(m->data.tableVal);
    avm_tabledecref(m->data.tableVal);
}

// TODO CHECK ORDER
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

void avm_warning(const char *format, ...) {
    static char buffer[WARNING_BUFF_SIZE] = {0};
    sprintf(buffer, "[Warning] %s", format);
    va_list args;
    va_start(args,format);
    vfprintf(stderr, buffer, args); 
    va_end(args);
}

void avm_error(const char *format, ...) {
    static char buffer[WARNING_BUFF_SIZE] = {0};
    sprintf(buffer, "[Error] %s", format);
    va_list args;
    va_start(args,format);
    vfprintf(stderr, buffer, args); 
    va_end(args);
}

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
}

void avm_decsp (void) {
    if (!sp) {
        avm_error("Stack overflow\n");
        executionFinished = true;
        return;
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

userfunc avm_getfuncinfo (unsigned addr) {
    // TODO
}

unsigned avm_getenvval(unsigned int i) {
	assert(stack[i].type == number_m);
	unsigned val = static_cast<unsigned>(stack[i].data.numVal);
	assert(stack[i].data.numVal == static_cast<double>(val));
	return val;
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
	char *strBuf;
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