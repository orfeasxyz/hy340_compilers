#include "../include/parser.h"
#include "../include/environment.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

#define nl	'\n'
#ifdef DEBUG
#	define DLOG_V(v)	std::cerr << #v << " :\n"  << v << nl
#else
#	define DLOG_V(v)
#endif

static std::string vmopcode_str[] = {
    "assign_v",
    "add_v",
    "sub_v",
    "mul_v",
    "div_v",
    "mod_v",
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

static std::string vmarg_str[] = {
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

// ---- Printing Utilities ----
std::string vmopcode2str(vmopcode_e vmop) {
	return vmopcode_str[vmop];
}

std::string vmarg2str(vmarg_e vma) {
	return vmarg_str[vma];
}

std::ostream& operator<<(std::ostream& os, const vmarg vma) {
	return os << "[" << vmarg2str(vma.type) << ", " << vma.val << "]";
}

std::ostream& operator<<(std::ostream& os, const instruction &inst) {
	os << std::setw(14) << vmopcode2str(inst.op) << " ";
	switch (inst.op) {
		case jump_v:
		case funcenter_v:
		case funcexit_v:
		case newtable_v:
			os << std::setw(12) << inst.result;
			break;
		case pusharg_v:
		case call_v:
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

std::ostream& operator<<(std::ostream& os, const userFunc &func) {
	return os << "[" << func.address << "]" << " " << func.id << " : " << func.localSize;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v) {
	int i = 0;
	for (const T& e : v) {
		os << std::setw(3) << i++ << " : " << e << nl;
	}
	return os;
}

// ---- Parsing ----
std::string freadString(FILE *f) {
	std::string res;
	char c;
	while ((c = fgetc(f)) != 0)
		res += c;
	return res;
}

void parseBinary(char* filename) {
	FILE* fin = fopen(filename, "rb");

	if(!fin) {
		printf("Error: Could not create file %s\n", filename);
		exit(1);
	}

	unsigned magic;
	fread(&magic, sizeof(magic), 1, fin);
	assert(magic == 340200501u);

	fread(&globalsCount, sizeof(globalsCount), 1, fin);
	// strings
	int nStrings;
	fread(&nStrings, sizeof(nStrings), 1, fin);
	strConsts.resize(nStrings);
	for (auto &s : strConsts) {
		s = freadString(fin);
	}
	DLOG_V(strConsts);

	// numbers
	int nNumConsts;
	fread(&nNumConsts, sizeof(nNumConsts), 1, fin);
	numConsts.resize(nNumConsts);
	for (auto &n : numConsts) {
		fread(&n, sizeof(n), 1, fin);
	}
	DLOG_V(numConsts);

	// functions
	int nUserFuncs;
	fread(&nUserFuncs, sizeof(nUserFuncs), 1, fin);
	userFuncs.resize(nUserFuncs);
	for (auto &func : userFuncs) {
		fread(&func.address, sizeof(func.address), 1, fin);
		fread(&func.localSize, sizeof(func.localSize), 1, fin);
		func.id = freadString(fin);
	}
	DLOG_V(userFuncs);

	// libfuncs
	int nLibFuncs;
	fread(&nLibFuncs, sizeof(nLibFuncs), 1, fin);
	libFuncs.resize(nLibFuncs);
	for (auto &func : libFuncs) {
		func = freadString(fin);
	}
	DLOG_V(libFuncs);

	// instructions
	int nInstructions;
	fread(&nInstructions, sizeof(nInstructions), 1, fin);
	instructions.resize(nInstructions);
	for (auto &inst : instructions) {
		fread(&inst, sizeof(inst), 1, fin);
	}
	DLOG_V(instructions);

	fclose(fin);
}
