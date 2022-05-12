#ifndef _RULE_HANDLERS_H_
#define _RULE_HANDLERS_H_

#include "structs.h"
#include "symtable.h"

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(char*, int);
SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(char*, int);
SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(char*, int);
void HANDLE_TERM_TO_INC_LVALUE(SymbolTableEntry*, int);
void HANDLE_TERM_TO_LVALUE_INC(SymbolTableEntry*, int);
void HANDLE_TERM_TO_DEC_LVALUE(SymbolTableEntry*, int);
void HANDLE_TERM_TO_LVALUE_DEC(SymbolTableEntry*, int);
void HANDLE_PRIM_TO_LVALUE(SymbolTableEntry*, int);
Expr* HANDLE_FUNCPREFIX(char*, int);
Expr* HANDLE_FUNCDEF(Expr*, unsigned, int);
char* HANDLE_IDLIST_IDENT(char*, int);
char* HANDLE_FUNCTION_WITH_NAME(char*, int);
char* HANDLE_FUNCTION_WITHOUT_NAME(int);
void HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry*, int);
void libFunc(SymTable_T, char*);

#endif  // _RULE_HANDLERS_H_
