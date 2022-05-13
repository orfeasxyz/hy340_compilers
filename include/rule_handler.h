#ifndef _RULE_HANDLERS_H_
#define _RULE_HANDLERS_H_

#include "structs.h"
#include "symtable.h"

void libFunc(SymTable_T, char*);
Expr* HANDLE_LVALUE_TO_IDENT(char*, int);
Expr* HANDLE_LVALUE_TO_LOCAL_IDENT(char*, int);
Expr* HANDLE_LVALUE_TO_GLOBAL_IDENT(char*, int);
void HANDLE_TERM_TO_INC_LVALUE(Expr*, int);
void HANDLE_TERM_TO_LVALUE_INC(Expr*, int);
void HANDLE_TERM_TO_DEC_LVALUE(Expr*, int);
void HANDLE_TERM_TO_LVALUE_DEC(Expr*, int);
Expr* HANDLE_PRIM_TO_LVALUE(Expr*, int);
SymbolTableEntry* HANDLE_FUNCPREFIX(char*, int);
SymbolTableEntry* HANDLE_FUNCDEF(SymbolTableEntry*, unsigned, int);
char* HANDLE_IDLIST_IDENT(char*, int);
char* HANDLE_FUNCTION_WITH_NAME(char*, int);
char* HANDLE_FUNCTION_WITHOUT_NAME(int);
Expr* HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(Expr*, Expr*, int);
Expr* HANDLE_MEMBER_TO_LVALUE_DOT_IDENT(Expr*, char*);
Expr* HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR(Expr*, Expr*);



#endif  // _RULE_HANDLERS_H_
