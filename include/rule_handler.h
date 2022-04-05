#ifndef _RULE_HANDLERS_H_
#define _RULE_HANDLERS_H_

#include "structs.h"
#include "symtable.h"

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(SymTable_T, char*, int, int);
SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(SymTable_T, SymTable_T, char*, int, int);
SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(SymTable_T, char*, int, int);
void              HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry* , int);

#endif // _RULE_HANDLERS_H_
