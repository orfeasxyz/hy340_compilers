#include "../include/rule_handler.h"
#include "../include/symtable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isVar(SymbolTableEntry* temp){
    return temp->type == VAR_FORMAL || temp->type == VAR_GLOBAL || temp->type == VAR_LOCAL;
}

Variable* makeVar(char* key, int lineno, int scope){
    Variable* temp = malloc(sizeof(struct Variable));
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;

    return temp;
}

Function* makeFunc(char* key, int lineno, int scope){
    Function* temp = malloc(sizeof(struct Function));
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;

	return temp;
}

void libFunc(SymTable_T head, char* name){
    SymbolTableEntry* temp_entry = malloc(sizeof(struct SymbolTableEntry));
    Function* temp = makeFunc(name, 0, 0);

    temp_entry->isActive = 1;
    temp_entry->type = LIBFUNC;
    temp_entry->value.funcVal = temp;
    
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

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(SymTable_T table, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup(table, key))) return temp;

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);

    temp->value.varVal = makeVar(key, lineno, scope);

    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(SymTable_T table, SymTable_T global, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(table, key))) return temp;

    if((temp = SymTable_lookup_here(global, key)) && temp->type == LIBFUNC){
        fprintf(stderr, "Library function %s can't be shadowed by local variable\n", temp->value.funcVal->name);
        return NULL;
    }

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);

    temp->value.varVal = makeVar(key, lineno, scope);

    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(SymTable_T global, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(global, key))) return temp;

    fprintf(stderr, "Name %s was not found in the global scope but was referenced as ::%s\n", key ,key);

    return NULL;
}

void HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be an lvalue to an assignment\n", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}

char* HANDLE_IDLIST_IDENT(SymTable_T table, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(table, key))){
        fprintf(stderr, "Formal argument %s already defined in the same id_list\n", key);
        return NULL;
    }

    if((temp = SymTable_lookup(table, key))){
        if(!isVar(temp)){
            fprintf(stderr, "Function with name %s is active, can't initialize formal argument with same name\n", key);
            return NULL;
        }
    }

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = VAR_FORMAL;

    temp->value.varVal = makeVar(key, lineno, scope);

    SymTable_insert(table, key, temp);

    return temp->value.varVal->name;
}

char* HANDLE_FUNCTION_WITH_NAME(SymTable_T table, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup(table, key))){
        if(isVar(temp)){
            fprintf(stderr, "Can't redefine variable %s as function\n", key);
            return NULL;
        }

        if(temp->type == LIBFUNC){
            fprintf(stderr, "Can't overshadow library function %s\n", key);
            return NULL;
        }

        if(temp->value.funcVal->scope == scope){
            fprintf(stderr, "Can't redefine the same function %s\n", key);
            return NULL;
        }
    } 

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = USERFUNC;

    temp->value.funcVal = makeFunc(key, lineno, scope);

    SymTable_insert(table, key, temp);

	return temp->value.funcVal->name;
}

char* HANDLE_FUNCTION_WITHOUT_NAME(SymTable_T table, int anon_count, int lineno, int scope){
    SymbolTableEntry* temp;
    char* funcname = malloc(countDigits(anon_count) + 2);

    sprintf(funcname, "$%d", anon_count);

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = USERFUNC;

    temp->value.funcVal = makeFunc(funcname, lineno, scope);

    SymTable_insert(table, funcname, temp);

	return temp->value.funcVal->name;
}

void HANDLE_TERM_TO_INC_LVALUE(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be referenced after ++ operator\n", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}

void HANDLE_TERM_TO_LVALUE_INC(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be referenced before ++ operator\n", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}

void HANDLE_TERM_TO_DEC_LVALUE(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be referenced after -- operator\n", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}

void HANDLE_TERM_TO_LVALUE_DEC(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be referenced before -- operator\n", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}

void HANDLE_PRIM_TO_LVALUE(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)) return;


    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}