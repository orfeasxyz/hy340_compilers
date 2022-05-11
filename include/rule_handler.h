#ifndef _RULE_HANDLERS_H_
#define _RULE_HANDLERS_H_

#include "structs.h"
#include "symtable.h"

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(SymTable_T, char*, int, int);
SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(SymTable_T, SymTable_T, char*,
                                               int, int);
SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(SymTable_T, char*, int, int);
void HANDLE_TERM_TO_INC_LVALUE(SymbolTableEntry*, int, int);
void HANDLE_TERM_TO_LVALUE_INC(SymbolTableEntry*, int, int);
void HANDLE_TERM_TO_DEC_LVALUE(SymbolTableEntry*, int, int);
void HANDLE_TERM_TO_LVALUE_DEC(SymbolTableEntry*, int, int);
void HANDLE_PRIM_TO_LVALUE(SymbolTableEntry*, int, int);
char* HANDLE_IDLIST_IDENT(SymTable_T, char*, int, int);
char* HANDLE_FUNCTION_WITH_NAME(SymTable_T, char*, int, int);
char* HANDLE_FUNCTION_WITHOUT_NAME(SymTable_T, int, int, int);
void HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry*, int ,int);
void libFunc(SymTable_T, char*);

#endif  // _RULE_HANDLERS_H_
