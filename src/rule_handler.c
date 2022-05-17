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
    scopeOffsetStack = stack_push(scopeOffsetStack, currScopeOffset());
    enterScopeSpace();
    resetFormalArgsOffset();

    return temp;
}

SymbolTableEntry* HANDLE_FUNCDEF(SymbolTableEntry* funcprefix, unsigned funcbody, int lineno){
    Expr* arg = newExpr(programfunc_e);

    arg->sym = funcprefix;
    arg->strConst = funcprefix->name;

    functionScopeStack = stack_pop(functionScopeStack);
    exitScopeSpace();
    funcprefix->totalLocals = funcbody;
    scopeOffsetStack = stack_pop(scopeOffsetStack);
    restoreCurrScopeOffset(stack_top(scopeOffsetStack));
    emit(funcend, arg, NULL, NULL, 0, lineno);
	return funcprefix;
}

// =======================================================================================

Expr* HANDLE_TERM_TO_INC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))) 
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    checkArith(lvalue, "INC LVALUE");
    Expr* temp = newExpr(var_e);
    temp->sym = newTemp();
    if(lvalue->type == tableitem_e){
        Expr* val = emitIfTableItem(lvalue);
        emit(assign, val, NULL, temp, 0, lineno);
        emit(add, val, newExprConstNum(1), val, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, val, 0, lineno);
    } else {
        emit(assign, lvalue, NULL, temp, 0, lineno);
        emit(add, lvalue, newExprConstNum(1), lvalue, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_LVALUE_INC(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack)))
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    checkArith(lvalue, "LVALUE INC");
    Expr* temp;
    if(lvalue->type == tableitem_e){
        temp = emitIfTableItem(lvalue);
        emit(add, temp, newExprConstNum(1), temp, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, temp, 0, lineno);
    } else {
        emit(add, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        temp = newExpr(arithmexpr_e);
        temp->sym = newTemp();
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_DEC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack)))
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    checkArith(lvalue, "DEC LVALUE");
    Expr* temp = newExpr(var_e);
    temp->sym = newTemp();
    if(lvalue->type == tableitem_e){
        Expr* val = emitIfTableItem(lvalue);
        emit(assign, val, NULL, temp, 0, lineno);
        emit(sub, val, newExprConstNum(1), val, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, val, 0, lineno);
    } else {
        emit(assign, lvalue, NULL, temp, 0, lineno);
        emit(sub, lvalue, newExprConstNum(1), lvalue, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_LVALUE_DEC(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack)))
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));

    checkArith(lvalue, "LVALUE DEC");
    Expr* temp;
    if(lvalue->type == tableitem_e){
        temp = emitIfTableItem(lvalue);
        emit(sub, temp, newExprConstNum(1), temp, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, temp, 0, lineno);
    } else {
        emit(sub, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        temp = newExpr(arithmexpr_e);
        temp->sym = newTemp();
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_UMINUS_EXPR(Expr* expression){
    checkArith(expression, "Uminus expression");
    Expr* temp = newExpr(arithmexpr_e);
    temp->sym = newTemp();
    emit(uminus, expression, NULL, temp, 0, expression->sym->line);
    return temp;
}

Expr* HANDLE_TERM_TO_NOT_EXPR(Expr* expression){
    Expr* temp = newExpr(boolexpr_e);
    temp->sym = newTemp();
    emit(not, expression, NULL, temp, 0, expression->sym->line);
    return temp;
}

Expr* HANDLE_PRIM_TO_LVALUE(Expr* lvalue, int lineno){
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

// =======================================================================================

Expr* HANDLE_PRIM_TO_FUNCDEF(SymbolTableEntry* funcdef){
    Expr* temp = newExpr(programfunc_e);
    temp->sym = funcdef;
    return temp;
}

// =======================================================================================

Expr* makeCall (Expr* lvalue, Expr* reversed_elist) {
    Expr* func = emitIfTableItem(lvalue);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL, 0, lvalue->sym->line);
        reversed_elist = reversed_elist->next;
    }

    emit(call, func, NULL, NULL, 0, lvalue->sym->line);
    Expr* result = newExpr(var_e);
    result->sym = newTemp();
    emit(getretval, NULL, NULL, result, 0, lvalue->sym->line);
    return result;
}

Call* HANDLE_METHODCALL(char* name, Expr* elist){
    Call* temp = malloc(sizeof(Call));

    temp->elist = elist;
    temp->method = 1;
    temp->name = name;

    return temp; 
}

Expr* HANDLE_CALL_ELIST(Expr* call, Expr* elist){
    return makeCall(call, elist);
}

Expr* HANDLE_CALL_FUNCDEF_ELIST(SymbolTableEntry* funcdef, Expr* elist){
    Expr* func = newExpr(programfunc_e);
    func->sym = funcdef;
    return makeCall(func, elist);
}

Expr* HANDLE_CALL_LVALUE_SUFFIX(Expr* lvalue, Call* callsuffix){
    lvalue = emitIfTableItem(lvalue);
    if(callsuffix->method){
        Expr* t = lvalue;
        lvalue = emitIfTableItem(memberItem(t, callsuffix->name));
        callsuffix->elist->next = t;
    }
    return makeCall(lvalue, callsuffix->elist);
}

Call* HANDLE_NORMCALL(Expr* elist){
    Call* temp = malloc(sizeof(Call));

    temp->elist = elist;
    temp->method = 0;
    temp->name  = (char*) 0;

    return temp;
}

// =======================================================================================

Expr* HANDLE_INDEXELEM(Expr* index, Expr* value){
    value->index = index;
    return value;
}

Expr* HANDLE_ELIST_ADD(Expr* expression, Expr* elist){
    elist->next = expression;       /* DEPENDS ON LEFT-TO-RIGHT OR RIGHT-TO-LEFT INPUT READING */
    return elist;                   /* THIS IS FOR LEFT-TO-RIGHT AND RETURNS THE LIST INVERSED */
}

Expr* HANDLE_INDEXED_ADD(Expr* indexedelem, Expr* indexed){
    indexed->next = indexedelem;
    return indexed;                 /* SAME AS ABOVE !!! */
}

// =======================================================================================


Expr* HANDLE_OBJECTDEF_TO_ELIST(Expr* elist){
    Expr* t = newExpr(newtable_e);
    t->sym = newTemp();
    emit(tablecreate, t, NULL, NULL, 0, elist->sym->line);
    for(int i; elist; elist = elist->next){
        emit(tablesetelem, t, newExprConstNum(i++), elist, 0, elist->sym->line);
    }

    return t;
}

Expr* HANDLE_OBJECTDEF_TO_INDEXED(Expr* indexed){
    Expr* t = newExpr(newtable_e);
    t->sym = newTemp();
    emit(tablecreate, t, NULL, NULL, 0, indexed->sym->line);
    for(; indexed; indexed = indexed->next){
        emit(tablesetelem, t, indexed->index, indexed, 0, indexed->sym->line);
    }

    return t;
}

// =======================================================================================

iopcode switch_op(char* op){
    if(op == "+") return add;
    else if(op == "-") return sub;
    else if(op == "*") return mul;
    else if(op == "/") return mydiv;
    else if(op == "%") return mod;
    else if(op == ">") return if_greater;
    else if(op == ">=") return if_geatereq;
    else if(op == "<") return if_less;
    else if(op == "<=") return if_lesseq;
    else if(op == "==") return if_eq;
    else if(op == "!=") return if_noteq;
    else if(op == "&&") return and;
    else if(op == "||") return or;
    else assert(0);
}

int check_arith_eligible(Expr* temp){
    switch(temp->type){
        case programfunc_e:
        case libraryfunc_e:
        case boolexpr_e:
        case newtable_e:
        case constbool_e:
        case conststring_e:
        case nil_e:
            return -1;
        case constnum_e:
            return 1;
        default:
            return 0;
    }
}

Expr* HANDLE_ARITH_OP(char* op, Expr* expr1, Expr* expr2){
    Expr* temp;

    if(check_arith_eligible(expr1) == 1 && check_arith_eligible(expr2) == 1){
        return newExprConstNum(expr1->numConst + expr2->numConst);
    }

    if(check_arith_eligible(expr1) == -1) {
        fprintf(stderr, "Expression 1 in line %d has type %s which is not allowed in arithmetic expression\n", expr1->sym->line, str_iopcodeName[expr1->type]);
        return (Expr*) 0;
    }

    if(check_arith_eligible(expr2) == -1) {
        fprintf(stderr, "Expression 2 in line %d has type %s which is not allowed in arithmetic expression\n", expr2->sym->line, str_iopcodeName[expr2->type]);
        return (Expr*) 0;
    }

    temp = newExpr(arithmexpr_e);
    temp->sym = newTemp();
    emit(switch_op(op), expr1, expr2, temp, 0, expr1->sym->line);

    return temp;
}

Expr* HANDLE_REL_OP(char* op, Expr* expr1, Expr* expr2){
    Expr* temp;

    if(check_arith_eligible(expr1) == 1 && check_arith_eligible(expr2) == 1){
        int result;
        if(op == ">") result = (expr1 > expr2);
        else if(op == ">=") result = (expr1 >= expr2);
        else if(op == "<") result = (expr1 < expr2);
        else if(op == "<=") result = (expr1 <= expr2);
        else if(op == "==") result = (expr1 == expr2);
        else if(op == "!=") result = (expr1 != expr2);
        return newExprConstBool(result);
    }

    if(check_arith_eligible(expr1) == -1) {
        fprintf(stderr, "Expression 1 in line %d has type %s which is not allowed in relation expression\n", expr1->sym->line, str_iopcodeName[expr1->type]);
        return (Expr*) 0;
    }

    if(check_arith_eligible(expr2) == -1) {
        fprintf(stderr, "Expression 2 in line %d has type %s which is not allowed in relation expression\n", expr2->sym->line, str_iopcodeName[expr2->type]);
        return (Expr*) 0;
    }

    //HERE

    temp = newExpr(boolexpr_e);
    temp->sym = newTemp();

    emit(switch_op(op), expr1, expr2, nextQuadLabel() + 3, 0, expr1->sym->line);
    emit(assign, newExprConstBool(0), NULL, temp, 0, expr1->sym->line);
    emit(jump, NULL, NULL, nextQuadLabel() + 2, 0, expr1->sym->line);
    emit(assign, newExprConstBool(1), NULL, temp, 0, expr1->sym->line);

    return temp;
}

Expr* HANDLE_BOOL_OP(char* op, Expr* expr1, Expr* expr2){
    Expr* temp;

    if(expr1->type == assignexpr_e || expr1->type == var_e) {
        fprintf(stderr, "Expression 1 in line %d has type %s which is not allowed in bool expression\n", expr1->sym->line, str_iopcodeName[expr1->type]);
        return (Expr*) 0;
    }

    if(expr2->type == assignexpr_e || expr2->type == var_e) {
        fprintf(stderr, "Expression 2 in line %d has type %s which is not allowed in bool expression\n", expr2->sym->line, str_iopcodeName[expr2->type]);
        return (Expr*) 0;
    }

    temp = newExpr(boolexpr_e);
    temp->sym = newTemp();
    emit(switch_op(op), expr1, expr2, temp, 0, expr1->sym->line);

    return temp;

}

// =======================================================================================

unsigned HANDLE_IFPREFIX(Expr* expression){
    unsigned temp;

    emit(if_eq, expression, newExprConstBool(1), nextQuadLabel() + 2, 0, expression->sym->line);
    temp = nextQuadLabel();
    emit(jump, NULL, NULL, 0, 0, expression->sym->line);

    return temp;
}

unsigned HANDLE_ELSEPREFIX(int lineno){
    unsigned temp = nextQuadLabel();
    
    emit(jump, NULL, NULL, 0, 0, lineno);

    return temp;
}


