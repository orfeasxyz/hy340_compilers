#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "structs.h" // avm_memcell, avm_table
#include "environment.h" // registers, const values tables

avm_memcell*	avm_translate_operand (vmarg *arg, avm_memcell *reg);

#endif // TRANSLATE_H
