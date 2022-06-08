#include <iomanip>
#include <iostream>
#include <vector>
#include <cassert>
#define nl	'\n'

#ifdef DEBUG
#	define DPRINTF(...)	fprintf(stderr, ...)
#	define PRINT_V(v)	std::cerr << #v << " :\n"  << v << nl
#else
#	define DPRINTF(...)
#	define PRINT_V(v)
#endif

#define MAX_STRLEN		1024

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::ostream;

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
    funcexit_v,
    newtable_v,
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

string vmopcode_str[] = {
    "assign_v",
    "add_v",
    "sub_v",
    "mul_v",
    "div_v",
    "mod_v",
    "uminus_v",
    "and_v",
    "or_v",
    "not_v",
    "jump_v",
    "jeq_v",
    "jne_v",
    "jle_v",
    "jge_v",
    "jlt_v",
    "jgt_v",
    "call_v",
    "pusharg_v",
    "funcenter_v",
    "funcexit_v",
    "newtable_v",
    "tablegetelem_v",
    "tablesetelem_v",
    "nop_v"
 };

string vmarg_str[] = {
    "label_a",
    "global_a",
    "formal_a",
    "local_a",
    "number_a",
    "string_a",
    "bool_a",
    "nil_a",
    "userfunc_a",
    "libfunc_a",
    "retval_a"
};

string vmopcode2str(vmopcode_e vmop) {
	return vmopcode_str[vmop];
}

string vmarg2str(vmarg_e vma) {
	return vmarg_str[vma];
}

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
    string id;
} userfunc;

char* freadString(FILE *f) {
	static char str[MAX_STRLEN];
	size_t c = 0;
	while ((str[c++] = fgetc(f)) != 0)
		;
	return str;
}

ostream& operator<<(ostream& os, const vmarg_t vma) {
	return os << "[" << vmarg2str(vma.type) << ", " << vma.val << "]";
}

ostream& operator<<(ostream& os, const instruction &inst) {
	os << std::setw(14) << vmopcode2str(inst.op) << " ";
	switch (inst.op) {
		case jump_v:
		case funcenter_v:
		case funcexit_v:
			os << std::setw(12) << inst.result;
			break;
		case pusharg_v:
		case call_v:
		case newtable_v:
			os << std::setw(12) << inst.arg1 << " ";
			break;
		case assign_v:
			os << std::setw(12) << inst.result << " " << std::setw(12) << inst.arg1 << " ";
			break;
		default:
			os << std::setw(12) << inst.result << " " << std::setw(12) << inst.arg1 << " " << std::setw(12) << inst.arg2 << " ";
	}
	return os;
}

ostream& operator<<(ostream& os, const userfunc &func) {
	return os << "[" << func.address << "]" << " " << func.id << " : " << func.localSize;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v) {
	for (const T& e : v) {
		os << e << nl;
	}
	return os;
}

int main(int argc, char **argv) {
	assert(argc == 2);
	char *filename = argv[1];
	FILE* f = fopen(filename, "rb");

	if(!f) {
		printf("Error: Could not create file %s\n", filename);
		exit(1);
	}

	unsigned magic;
	fread(&magic, sizeof(magic), 1, f);
	assert(magic == 340200501u);

	// strings
	int currStrConsts;
	fread(&currStrConsts, sizeof(currStrConsts), 1, f);
	vector<string> strConsts(currStrConsts);
	for (auto &s : strConsts) {
		s = freadString(f);
	}
	PRINT_V(strConsts);

	// numbers
	int currNumConsts;
	fread(&currNumConsts, sizeof(currNumConsts), 1, f);
	vector<double> numConsts(currNumConsts);
	for (auto &n : numConsts) {
		fread(&n, sizeof(n), 1, f);
	}
	PRINT_V(numConsts);

	// functions
	int currUserFuncs;
	fread(&currUserFuncs, sizeof(currUserFuncs), 1, f);
	vector<userfunc> userFuncs(currUserFuncs);
	for (auto &func : userFuncs) {
		fread(&func.address, sizeof(func.address), 1, f);
		fread(&func.localSize, sizeof(func.localSize), 1, f);
		func.id = freadString(f);
	}
	PRINT_V(userFuncs);

	// libfuncs
	int currNameLibFuncs;
	fread(&currNameLibFuncs, sizeof(currNameLibFuncs), 1, f);
	vector<string> nameLibFuncs(currNameLibFuncs);
	for (auto &func : nameLibFuncs) {
		func = freadString(f);
	}
	PRINT_V(nameLibFuncs);

	// instructions
	int currInstruction;
	fread(&currInstruction, sizeof(currInstruction), 1, f);
	vector<instruction> instructions(currInstruction);
	for (auto &inst : instructions) {
		fread(&inst, sizeof(inst), 1, f);
	}
	PRINT_V(instructions);

	fclose(f);
	return 0;
}
