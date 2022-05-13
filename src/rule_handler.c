#include "../include/rule_handler.h"
#include "../include/symtable.h"
#include "../include/structs.h"
#include "../include/stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Expr* emitIfTableItem(Expr* e);

int isVar(SymbolTableEntry* temp){
    return temp->type == VAR_FORMAL || temp->type == VAR_GLOBAL || temp->type == VAR_LOCAL;
}

Expr* makeExpr(SymbolTableEntry* sym){
    assert(sym);
    Expr* e = (Expr*) malloc(sizeof(Expr));
    memset(e, 0, sizeof(Expr));
    e->next = (Expr*) 0;
    e->sym = sym;

    if(isVar(sym))                   e->type = var_e;
    else if(sym->type == USERFUNC)   e->type = programfunc_e;
    else if(sym->type == LIBFUNC)    e->type = libraryfunc_e;
    else                             assert(0);

    return e;
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

// =======================================================================================


Expr* HANDLE_LVALUE_TO_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup(table, key))) return makeExpr(temp);

    temp = makeSymbol(key, lineno, scope);
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);
    temp->space = currScopeSpace();
    temp->offset = currScopeOffset();
    incCurrScopeOffset();

    return makeExpr(SymTable_insert(table, key, temp));
}

Expr* HANDLE_LVALUE_TO_LOCAL_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;
    SymTable_T table = current_table;

    if((temp = SymTable_lookup_here(table, key))) return makeExpr(temp);

    if((temp = SymTable_lookup_here(head, key)) && temp->type == LIBFUNC){
        fprintf(stderr, "Line %d: Library function %s can't be shadowed by local variable\n", lineno, temp->name);
        return NULL;
    }

    temp = makeSymbol(key, lineno, scope);
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);
    temp->space = currScopeSpace();
    temp->offset = currScopeOffset();
    incCurrScopeOffset();


    return  makeExpr(SymTable_insert(table, key, temp));
}

Expr* HANDLE_LVALUE_TO_GLOBAL_IDENT(char* key, int lineno){
    SymbolTableEntry* temp;

    if((temp = SymTable_lookup_here(head, key))) return makeExpr(temp);

    fprintf(stderr, "Line %d: Name %s was not found in the global scope but was referenced as ::%s\n", lineno, key ,key);

    return (Expr*) 0;
}

// =======================================================================================

Expr* HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(Expr* lvalue, Expr* expression, int lineno){
    // Wrong Syntax
    // if(!lvalue) return (Expr*) 0;;

    // if(!isVar(lvalue)){
    //     fprintf(stderr, "Line %d: Function %s can't be an lvalue to an assignment\n", lineno, lvalue->name);
    //     return (Expr*) 0;
    // }

    // if(!isLegal(lvalue->scope, stack_top(functionScopeStack)))
    //     fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->name, lvalue->scope, stack_top(functionScopeStack));
    //     return (Expr*) 0;

    Expr* temp;

    if(lvalue->type == tableitem_e){
        emit(
            tablesetelem,
            lvalue,
            lvalue->index,
            expression,
            0,
            lineno
        );
        temp = emitIfTableItem(lvalue);
        temp->type = assignexpr_e;
    } else {
        emit(
            assign,
            expression,
            NULL,
            lvalue,
            0,
            lineno
        );
        temp = newExpr(assignexpr_e);
        temp->sym = newTemp();
        emit(
            assign,
            lvalue,
            NULL,
            temp,
            0,
            lineno
        );
    }
    return temp;   
}

// =======================================================================================

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

// =======================================================================================

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

SymbolTableEntry* HANDLE_FUNCPREFIX(char* func_name, int lineno){
    SymbolTableEntry* temp = SymTable_lookup(current_table ,func_name);
    Expr* arg = newExpr(programfunc_e);

    temp->iadress = nextQuadLabel();

    arg->sym = temp;
    arg->strConst = temp->name;

    emit(funcstart, arg, NULL, NULL, 0, lineno);
    stack_push(scopeOffsetStack, currScopeOffset());
    enterScopeSpace();
    resetFormalArgsOffset();

    return temp;
}

SymbolTableEntry* HANDLE_FUNCDEF(SymbolTableEntry* funcprefix, unsigned funcbody, int lineno){
    Expr* arg = newExpr(programfunc_e);

    arg->sym = funcprefix;
    arg->strConst = funcprefix->name;

    stack_pop(functionScopeStack);
    exitScopeSpace();
    funcprefix->totalLocals = funcbody;
    stack_pop(scopeOffsetStack);
    restoreCurrScopeOffset(stack_top(scopeOffsetStack));
    emit(funcend, arg, NULL, NULL, 0, lineno);
	return funcprefix;
}

// =======================================================================================

void HANDLE_TERM_TO_INC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return;

    if(!isVar(lvalue->sym)){
        fprintf(stderr, "Line %d: Function %s can't be referenced after ++ operator\n", lineno, lvalue->sym->name);
        return;
    }

    if(isLegal(lvalue->sym->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_LVALUE_INC(Expr* lvalue, int lineno){
    if(!lvalue) return;

    if(!isVar(lvalue->sym)){
        fprintf(stderr, "Line %d: Function %s can't be referenced before ++ operator\n", lineno, lvalue->sym->name);
        return;
    }

    if(isLegal(lvalue->sym->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_DEC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return;

    if(!isVar(lvalue->sym)){
        fprintf(stderr, "Line %d: Function %s can't be referenced after -- operator\n", lineno, lvalue->sym->name);
        return;
    }

    if(isLegal(lvalue->sym->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    return;
}

void HANDLE_TERM_TO_LVALUE_DEC(Expr* lvalue, int lineno){
    if(!lvalue) return;

    if(!isVar(lvalue->sym)){
        fprintf(stderr, "Line %d: Function %s can't be referenced before -- operator\n", lineno, lvalue->sym->name);
        return;
    }

    if(isLegal(lvalue->sym->scope, stack_top(functionScopeStack))) return;

    fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    return;
}

Expr* HANDLE_PRIM_TO_LVALUE(Expr* lvalue, int lineno){
    // Syntax ???                                                                NOTICE ME HERE PLEASEEEEE
    return emitIfTableItem(lvalue);
}

// =======================================================================================

Expr* emitIfTableItem(Expr* e){
    if(e->type != tableitem_e) return e;
    else{
        Expr* result = newExpr(var_e);
        result->sym = newTemp();
        emit(
            tablegetelem,
            e,
            e->index,
            result,
            0,
            e->sym->line
        );
        return result;
    }
}

Expr* memberItem (Expr* lv, char* name) {
    lv = emitIfTableItem(lv); 
    Expr* ti = newExpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newExprConstString(name);
    return ti;
}

Expr* HANDLE_MEMBER_TO_LVALUE_DOT_IDENT(Expr* lvalue, char* name){
    return memberItem(lvalue, name);
}

Expr* HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR(Expr* lvalue, Expr* expression){
    lvalue = emitIfTableItem(lvalue);
    Expr* temp = newExpr(tableitem_e);
    temp->sym = lvalue->sym;
    temp->index = expression->index;
    return temp;
}

