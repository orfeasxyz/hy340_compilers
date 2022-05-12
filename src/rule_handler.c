#include "../include/rule_handler.h"
#include "../include/symtable.h"
#include "../include/structs.h"
#include "../include/stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isVar(SymbolTableEntry* temp){
    return temp->type == VAR_FORMAL || temp->type == VAR_GLOBAL || temp->type == VAR_LOCAL;
}

SymbolTableEntry* makeSymbol(char* key, int lineno, int scope){
    SymbolTableEntry* temp = malloc(sizeof(SymbolTableEntry));
    temp->isActive = 1;
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;

    return temp;
}


void libFunc(SymTable_T head, char* name){
    SymbolTableEntry* temp_entry = makeSymbol(name, 0, 0);
    temp_entry->type = LIBFUNC;
    
    SymTable_insert(head, name, temp_entry);
}

int isLegal(int scope, int func_scope){
    return (scope == 0 || scope > func_scope);
}

int countDigits(int num){
    int count = 0;
    while(num){
        num /= 10;
        count++;
    }

    return count;
}

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup(table, key))) return temp;

    temp = makeSymbol(key, lineno, scope);
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);
    temp->space = currScopeSpace();
    temp->offset = currScopeOffset();
    incCurrScopeOffset();

    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup_here(table, key))) return temp;

    if((temp = SymTable_lookup_here(head, key)) && temp->type == LIBFUNC){
        fprintf(stderr, "Line %d: Library function %s can't be shadowed by local variable\n", lineno, temp->name);
        return NULL;
    }

    temp = makeSymbol(key, lineno, scope);
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);
    temp->space = currScopeSpace();
    temp->offset = currScopeOffset();
    incCurrScopeOffset();


    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(head, key))) return temp;

    fprintf(stderr, "Line %d: Name %s was not found in the global scope but was referenced as ::%s\n", lineno, key ,key);

    return NULL;
}

void HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Line %d: Function %s can't be an lvalue to an assignment\n", lineno, entry->name);
        return;
    }

    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}

char* HANDLE_IDLIST_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup_here(table, key))){
        fprintf(stderr, "Line %d: Formal argument %s already defined in the same id_list\n", lineno, key);
        return NULL;
    }

    if((temp = SymTable_lookup(table, key))){
        if(!isVar(temp)){
            fprintf(stderr, "Line %d: Function with name %s is active, can't initialize formal argument with same name\n", lineno, key);
            return NULL;
        }
    }

    temp = makeSymbol(key, lineno, scope);
    temp->type = VAR_FORMAL;

    SymTable_insert(table, key, temp);

    return temp->name;
}

char* HANDLE_FUNCTION_WITH_NAME(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup(table, key))){
        if(isVar(temp)){
            fprintf(stderr, "Line %d: Can't redefine variable %s as function\n", lineno, key);
            return NULL;
        }

        if(temp->type == LIBFUNC){
            fprintf(stderr, "Line %d: Can't overshadow library function %s\n", lineno, key);
            return NULL;
        }

        if(temp->scope == scope){
            fprintf(stderr, "Line %d: Can't redefine the same function %s\n", lineno, key);
            return NULL;
        }
    } 

    temp = makeSymbol(key, lineno, scope);
    temp->type = USERFUNC;

    SymTable_insert(table, key, temp);

	return temp->name;
}

char* HANDLE_FUNCTION_WITHOUT_NAME(int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;
    char* funcname = malloc(countDigits(anon_count) + 2);

    sprintf(funcname, "$%d", anon_count);

    temp = makeSymbol(funcname, lineno, scope);
    temp->type = USERFUNC;

    SymTable_insert(table, funcname, temp);

	return temp->name;
}

Expr* HANDLE_FUNCPREFIX(char* func_name, int lineno){
    SymbolTableEntry* temp = SymTable_lookup(current_table ,func_name);
    Expr* arg = malloc(sizeof(Expr));

    temp->iadress = nextQuadLabel();

    arg->sym = temp;
    arg->type = programfunc_e;
    arg->strConst = temp->name;

    emit(funcstart, arg, NULL, NULL, 0, lineno);
    stack_push(scopeOffsetStack, currScopeOffset());
    enterScopeSpace();
    resetFormalArgsOffset();

    return arg;
}

Expr* HANDLE_FUNCDEF(Expr* funcprefix, unsigned funcbody, int lineno){
    stack_pop(functionScopeStack);
    exitScopeSpace();
    funcprefix->sym->totalLocals = funcbody;
    stack_pop(scopeOffsetStack);
    restoreCurrScopeOffset(stack_top(scopeOffsetStack));
    emit(funcend, funcprefix, NULL, NULL, 0, lineno);
	return funcprefix;
}

void HANDLE_TERM_TO_INC_LVALUE(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Line %d: Function %s can't be referenced after ++ operator\n", lineno, entry->name);
        return;
    }

    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_LVALUE_INC(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Line %d: Function %s can't be referenced before ++ operator\n", lineno, entry->name);
        return;
    }

    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_DEC_LVALUE(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Line %d: Function %s can't be referenced after -- operator\n", lineno, entry->name);
        return;
    }

    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_LVALUE_DEC(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Line %d: Function %s can't be referenced before -- operator\n", lineno, entry->name);
        return;
    }

    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_PRIM_TO_LVALUE(SymbolTableEntry* entry, int lineno){
    if(!entry) return;

    if(!isVar(entry)) return;


    if(isLegal(entry->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, entry->name, entry->scope, stack_top(functionScopeStack));

    return;
}
