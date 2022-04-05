#include "rule_handler.h"
#include "symtable.h"
#include <string.h>
#include <stdio.h>

int isVar(SymbolTableEntry* temp){
    return temp->type == VAR_FORMAL || temp->type == VAR_GLOBAL || temp->type == VAR_LOCAL;
}

int isLegal(int scope, int func_scope){
    return (scope == 0 || scope > func_scope);
}

SymbolTableEntry* HANDLE_LVALUE_TO_IDENT(SymTable_T table, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup(table, key))) return temp;

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);

    Variable* temp_var = malloc(sizeof(struct Variable));
    temp_var->name = malloc(strlen(key) + 1);
    strcpy(temp_var->name, key);
    temp_var->line = lineno;
    temp_var->scope = scope;

    temp->value.varVal = temp_var;

    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_LOCAL_IDENT(SymTable_T table, SymTable_T global, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(table, key))){
        if(!isVar(temp)){
            fprintf(stderr, "Function %s referenced after keyword LOCAL\n", key);
            return NULL;
        }

        return temp;
    }

    else if((temp = SymTable_lookup_here(global, key))){
        if(!isVar(temp)){
            fprintf(stderr, "Function %s referenced after keyword LOCAL\n", key);
            return NULL;
        }

        return temp;
    }

    temp = malloc(sizeof(struct SymbolTableEntry));
    temp->isActive = 1;
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);

    Variable* temp_var = malloc(sizeof(struct Variable));
    temp_var->name = malloc(strlen(key) + 1);
    strcpy(temp_var->name, key);
    temp_var->line = lineno;
    temp_var->scope = scope;

    temp->value.varVal = temp_var;

    return SymTable_insert(table, key, temp);
}

SymbolTableEntry* HANDLE_LVALUE_TO_GLOBAL_IDENT(SymTable_T global, char* key, int lineno, int scope){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(global, key))) return temp;

    fprintf(stderr, "Variable %s was not found in the global scope but was referenced as ::%s\n", key ,key);

    return NULL;
}

void HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(SymbolTableEntry* entry, int func_scope){
    if(!entry) return;

    if(!isVar(entry)){
        fprintf(stderr, "Function %s can't be an lvalue to an assignment", entry->value.funcVal->name);
        return;
    }

    if(isLegal(entry->value.varVal->scope, func_scope)) return;

    fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d", entry->value.varVal->name, entry->value.varVal->scope, func_scope);

    return;
}
