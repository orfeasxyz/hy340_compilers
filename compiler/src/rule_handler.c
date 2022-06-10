#include "../include/rule_handler.h"
#include "../include/symtable.h"
#include "../include/structs.h"
#include "../include/stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifdef DEBUG
#	define DPRINT(...) fprintf(stderr, __VA_ARGS__)
#else
#	define DPRINT(...)
#endif


Expr* emitIfTableItem(Expr* e, int lineno);

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
        exit(1);
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
    exit(1);
}

// =======================================================================================

Expr* HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION(Expr* lvalue, Expr* expression, int lineno){
    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))){
        fprintf(stderr, "Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));
        exit(1);
    }

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
        temp = emitIfTableItem(lvalue, lineno);
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
        temp->sym = newTemp(lineno);
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
        exit(1);
    }

    if((temp = SymTable_lookup_here(table, key))){
        if(!isVar(temp)){
            fprintf(stderr, "Line %d: Function with name %s is active, can't initialize formal argument with same name\n", lineno, key);
            exit(1);
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
            exit(1);
        }

        if(temp->type == LIBFUNC){
            fprintf(stderr, "Line %d: Can't overshadow library function %s\n", lineno, key);
            exit(1);
        }

        if(temp->scope == scope){
            fprintf(stderr, "Line %d: Can't redefine the same function %s\n", lineno, key);
            exit(1);
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

    sprintf(funcname, "$%d", anon_count++);

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

    emit(funcstart, NULL, NULL, arg, 0, lineno);
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
    emit(funcend, NULL, NULL, arg, 0, lineno);
	return funcprefix;
}

// =======================================================================================

Expr* HANDLE_TERM_TO_INC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))){
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));
        exit(1);
    }

    checkArith(lvalue, "INC LVALUE");
    Expr* temp = newExpr(var_e);
    temp->sym = newTemp(lineno);
    if(lvalue->type == tableitem_e){
        Expr* val = emitIfTableItem(lvalue, lineno);
        emit(assign, val, NULL, temp, 0, lineno);
        emit(add, val, newExprConstNum(1), val, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, val, 0, lineno);
    } else {
        emit(add, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_LVALUE_INC(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))){
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));
        exit(1);
    }

    checkArith(lvalue, "LVALUE INC");
    Expr* temp;
    if(lvalue->type == tableitem_e){
        temp = emitIfTableItem(lvalue, lineno);
        emit(add, temp, newExprConstNum(1), temp, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, temp, 0, lineno);
    } else {
        emit(add, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        temp = newExpr(arithmexpr_e);
        temp->sym = newTemp(lineno);
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_DEC_LVALUE(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))){
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));
        exit(1);
    }

    checkArith(lvalue, "DEC LVALUE");   
    Expr* temp = newExpr(var_e);
    temp->sym = newTemp(lineno);
    if(lvalue->type == tableitem_e){
        Expr* val = emitIfTableItem(lvalue, lineno);
        emit(assign, val, NULL, temp, 0, lineno);
        emit(sub, val, newExprConstNum(1), val, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, val, 0, lineno);
    } else {
        emit(sub, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_LVALUE_DEC(Expr* lvalue, int lineno){
    if(!lvalue) return (Expr*) 0;

    if(!isLegal(lvalue->sym->scope, stack_top(functionScopeStack))){
        fprintf(stderr, "Line %d: Variable %s at scope %d is inaccessible due to function declaration at scope %d\n", lineno, lvalue->sym->name, lvalue->sym->scope, stack_top(functionScopeStack));
        exit(1);
    }

    checkArith(lvalue, "LVALUE DEC");
    Expr* temp;
    if(lvalue->type == tableitem_e){
        temp = emitIfTableItem(lvalue, lineno);
        emit(sub, temp, newExprConstNum(1), temp, 0, lineno);
        emit(tablesetelem, lvalue, lvalue->index, temp, 0, lineno);
    } else {
        emit(sub, lvalue, newExprConstNum(1), lvalue, 0, lineno);
        temp = newExpr(arithmexpr_e);
        temp->sym = newTemp(lineno);
        emit(assign, lvalue, NULL, temp, 0, lineno);
    }

    return temp;
}

Expr* HANDLE_TERM_TO_UMINUS_EXPR(Expr* expression, int lineno){
    checkArith(expression, "Uminus expression");
    Expr* temp = newExpr(arithmexpr_e);
    temp->sym = newTemp(lineno);
    emit(uminus, expression, NULL, temp, 0, lineno);
    return temp;
}

void notBoolExpr(Expr* expression, int lineno){
    expression->trueList = newList(nextQuadLabel());
    expression->falseList = newList(nextQuadLabel() + 1);
    emit(if_eq, expression, newExprConstBool(1), NULL, 0, lineno);
    emit(jump, NULL, NULL, NULL, 0, lineno);
}

Expr* HANDLE_TERM_TO_NOT_EXPR(Expr* expression, int lineno)
{
    Expr* temp = newExpr(boolexpr_e);
    temp->sym = newTemp(lineno);

    if (expression->type == var_e ||  expression->type == assignexpr_e) notBoolExpr(expression, lineno);
    temp->trueList = expression->falseList;
    temp->falseList = expression->trueList;

    return temp;
}

Expr* HANDLE_PRIM_TO_LVALUE(Expr* lvalue, int lineno){
    return emitIfTableItem(lvalue, lineno);
}

// =======================================================================================

Expr* emitIfTableItem(Expr* e, int lineno){
    if(e->type != tableitem_e) return e;
    else{
        Expr* result = newExpr(var_e);
        result->sym = newTemp(lineno);
        emit(
            tablegetelem,
            e,
            e->index,
            result,
            0,
            lineno
        );
        return result;
    }
}

Expr* memberItem (Expr* lv, char* name, int lineno) {
    lv = emitIfTableItem(lv, lineno); 
    Expr* ti = newExpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newExprConstString(name);
    return ti;
}

Expr* HANDLE_MEMBER_TO_LVALUE_DOT_IDENT(Expr* lvalue, char* name, int lineno){
    return memberItem(lvalue, name, lineno);
}

Expr* HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR(Expr* lvalue, Expr* expression, int lineno){
    lvalue = emitIfTableItem(lvalue, lineno);
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

Expr* makeCall (Expr* lvalue, Expr* reversed_elist, int lineno) {
    Expr* func = emitIfTableItem(lvalue, lineno);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL, 0, lineno);
        reversed_elist = reversed_elist->next;
    }

    emit(call, func, NULL, NULL, 0, lineno);
    Expr* result = newExpr(var_e);
    result->sym = newTemp(lineno);
    emit(getretval, NULL, NULL, result, 0, lineno);
    return result;
}


Expr* HANDLE_CALL_ELIST(Expr* call, Expr* elist, int lineno){
    return makeCall(call, elist, lineno);
}

Expr* HANDLE_CALL_FUNCDEF_ELIST(SymbolTableEntry* funcdef, Expr* elist, int lineno){
    Expr* func = newExpr(programfunc_e);
    func->sym = funcdef;
    return makeCall(func, elist, lineno);
}

Expr* HANDLE_CALL_LVALUE_SUFFIX(Expr* lvalue, Call* callsuffix, int lineno){
    lvalue = emitIfTableItem(lvalue, lineno);
    if(callsuffix->method){
        Expr* t = lvalue;
        lvalue = emitIfTableItem(memberItem(t, callsuffix->name, lineno), lineno);
        if(callsuffix->elist) callsuffix->elist->next = t;
        else callsuffix->elist = t;
    }
    return makeCall(lvalue, callsuffix->elist, lineno);
}

Call* HANDLE_NORMCALL(Expr* elist){
    Call* temp = malloc(sizeof(Call));

    temp->elist = elist;
    temp->method = 0;
    temp->name  = (char*) 0;

    return temp;
}

Call* HANDLE_METHODCALL(char* name, Expr* elist){
    Call* temp = malloc(sizeof(Call));

    temp->elist = elist;
    temp->method = 1;
    temp->name = name;

    return temp; 
}

// =======================================================================================

Expr* HANDLE_INDEXELEM(Expr* index, Expr* value){
    value->index = index;
    return value;
}

Expr* HANDLE_ELIST_ADD(Expr* expression, Expr* elist){
    expression->next = elist;
    return expression;
}

Expr* HANDLE_INDEXED_ADD(Expr* indexedelem, Expr* indexed){
    indexedelem->next = indexed; 
    return indexedelem;              /* SAME AS ABOVE !!! */
}

// =======================================================================================


Expr* HANDLE_OBJECTDEF_TO_ELIST(Expr* elist, int lineno){
    Expr* t = newExpr(newtable_e);
    t->sym = newTemp(lineno);
    emit(tablecreate, NULL, NULL, t, 0, lineno);
    for(int i = 0; elist; elist = elist->next){
        emit(tablesetelem, t, newExprConstNum(i++), elist, 0, lineno);
    }

    return t;
}

Expr* HANDLE_OBJECTDEF_TO_INDEXED(Expr* indexed, int lineno){
    Expr* t = newExpr(newtable_e);
    t->sym = newTemp(lineno);
    emit(tablecreate, NULL, NULL, t, 0, lineno);
    for(; indexed; indexed = indexed->next){
        emit(tablesetelem, t, indexed->index, indexed, 0, lineno);
    }

    return t;
}

// =======================================================================================
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

int check_bool_eligible(Expr* temp){
    switch(temp->type){
        case programfunc_e:
        case libraryfunc_e:
        case newtable_e:
        case constbool_e:
        case conststring_e:
        case constnum_e:
        case nil_e:
            return 1;
        default:
            return 0;
    }
}

Expr* HANDLE_ARITH_OP(iopcode op, Expr* expr1, Expr* expr2, int lineno){
    Expr* temp;

    if(check_arith_eligible(expr1) == 1 && check_arith_eligible(expr2) == 1){
        double res;
        switch(op){
            case add:   res = expr1->numConst + expr2->numConst; break;
            case sub:   res = expr1->numConst - expr2->numConst; break;
            case mul:   res = expr1->numConst * expr2->numConst; break;
            case mydiv: res = expr1->numConst / expr2->numConst; break;
            case mod:   res = (long long)expr1->numConst % (long long)expr2->numConst; break;
            default: assert(0);
        }
        return newExprConstNum(res);
    }

    if(check_arith_eligible(expr1) == -1) {
        fprintf(stderr, "Expression 1 in line %d has type %s which is not allowed in arithmetic expression\n", 0, str_iopcodeName[expr1->type]);
        exit(1);
    }

    if(check_arith_eligible(expr2) == -1) {
        fprintf(stderr, "Expression 2 in line %d has type %s which is not allowed in arithmetic expression\n",  0, str_iopcodeName[expr2->type]);
        exit(1);
    }

    temp = newExpr(arithmexpr_e);
    temp->sym = newTemp(lineno);
    emit(op, expr1, expr2, temp, 0, lineno);

    return temp;
}

Expr* HANDLE_REL_OP(iopcode op, Expr* expr1, Expr* expr2, int lineno){
    Expr* temp;

    if(check_arith_eligible(expr1) == 1  && check_arith_eligible(expr2) == 1){
        int res;
        if(op == if_greater)		res = (expr1->numConst > expr2->numConst);
        else if(op == if_geatereq)	res = (expr1->numConst >= expr2->numConst);
        else if(op == if_less)		res = (expr1->numConst < expr2->numConst);
        else if(op == if_lesseq)	res = (expr1->numConst <= expr2->numConst);
        else if(op == if_eq)		res = (expr1->numConst == expr2->numConst);
        else if(op == if_noteq)		res = (expr1->numConst != expr2->numConst);

        return newExprConstBool(res);
    }

    if((op == if_eq || op == if_noteq)){
        int res;

        if((expr1->type == nil_e && expr2->type == tableitem_e) || (expr1->type == tableitem_e && expr2->type == nil_e)){
            switch (op) {
                case if_eq:     return newExprConstBool(0);
                case if_noteq:  return newExprConstBool(1);
                default: ;
            }
        }

        if(expr1->type == expr2->type){
            switch (expr1->type) {
                case constnum_e:        res = expr2->numConst == expr1->numConst;               break;
                case conststring_e:     res = strcmp(expr2->strConst, expr1->strConst) == 0;    break;
                case newtable_e:        res = 1;                                                break;
                case programfunc_e:     res = strcmp(expr2->sym->name, expr1->sym->name) == 0;  break;
                case libraryfunc_e:     res = strcmp(expr2->sym->name, expr1->sym->name) == 0;  break;
                case constbool_e:       res = expr2->boolConst == expr1->boolConst;             break;
                default: goto QUIT;
            }

            return (op == if_eq ? newExprConstBool(res) : newExprConstBool(!res));
        }
    }

    QUIT:


    if(check_arith_eligible(expr1) == -1 && op != if_eq && op != if_noteq) {
        fprintf(stderr, "Expression 1 has type %s which is not allowed in relation expression\n", str_iopcodeName[expr1->type]);
        exit(1);
    }

    if(check_arith_eligible(expr2) == -1 && op != if_eq && op != if_noteq) {
        fprintf(stderr, "Expression 2 has type %s which is not allowed in relation expression\n", str_iopcodeName[expr2->type]);
        exit(1);
    }

    temp = newExpr(boolexpr_e);
    temp->sym = newTemp(lineno);
	temp->trueList = newList(nextQuadLabel());
	temp->falseList = newList(nextQuadLabel()+1);

    emit(op, expr1, expr2, NULL, 0, lineno);
    emit(jump, NULL, NULL, NULL, 0, lineno);

    return temp;
}

Expr* HANDLE_BOOL_OP(iopcode op, Expr* expr1, Expr* expr2, unsigned M, int lineno){
    Expr* temp;
    int isVar = 0;

	if (expr1->type == var_e ||  expr1->type == assignexpr_e) {
        notBoolExpr(expr1, lineno);
        isVar = 1;
	}

    if (expr2->type == var_e || expr2->type == assignexpr_e){
        notBoolExpr(expr2, lineno);
        isVar = 1;
    }

    patchList((op == and ? expr1->trueList : expr1->falseList), M);

	if(!isVar && check_bool_eligible(expr1) && check_bool_eligible(expr2)){
		switch (op) {
			case and:	temp = newExprConstBool(boolVal(expr1) && boolVal(expr2)); break;
			case or:	temp = newExprConstBool(boolVal(expr1) || boolVal(expr2)); break;
			default:	assert(0);
		}
	} else {
        temp = newExpr(boolexpr_e);
        temp->sym = newTemp(lineno);
    }

	switch (op) {
		case and:
			temp->trueList = expr2->trueList;
			temp->falseList = mergeList(expr1->falseList, expr2->falseList);
			break;
		case or:
			temp->falseList = expr2->falseList;
			temp->trueList = mergeList(expr1->trueList, expr2->trueList);
			break;
		default:	assert(0);
	}

    return temp;
}

// =======================================================================================

unsigned HANDLE_IFPREFIX(Expr* expression, int lineno){
    unsigned temp;

    emit(if_eq, expression, newExprConstBool(1), NULL, nextQuadLabel() + 2, lineno);
    temp = nextQuadLabel();
    emit(jump, NULL, NULL, NULL, 0, lineno);

    return temp;
}

unsigned HANDLE_ELSEPREFIX(int lineno){
    unsigned temp = nextQuadLabel();
    
    emit(jump, NULL, NULL, 0, 0, lineno);

    return temp;
}

unsigned HANDLE_WHILEARGS(Expr* expression, int lineno){
    unsigned result;
    emit(if_eq, expression, newExprConstBool(1), NULL, nextQuadLabel() + 2, lineno);
    result = nextQuadLabel();
    emit(jump, NULL, NULL, NULL, 0, lineno);
	return result;
}

void HANDLE_WHILE(unsigned start, unsigned args, stmt_t *stmt, int lineno){
    emit(jump, NULL, NULL, NULL, start, lineno);
    patchLabel(args, nextQuadLabel());

    if(stmt){
        patchList(stmt->breakList, nextQuadLabel());
        patchList(stmt->contList, start);
    }
}

ForLoopPrefix* HANDLE_FORPREFIX(unsigned M, Expr* expression, int lineno){
    ForLoopPrefix* temp = malloc(sizeof(ForLoopPrefix));
    temp->test = M;
    temp->enter = nextQuadLabel();
    emit(if_eq, expression, newExprConstBool(1), 0, 0, lineno);

    return temp;
}

void HANDLE_FORSTMT(ForLoopPrefix* prefix, unsigned N1, unsigned N2, unsigned N3, stmt_t* stmt){
    patchLabel(prefix->enter, N2 + 1);
    patchLabel(N1, nextQuadLabel());
    patchLabel(N2, prefix->test);
    patchLabel(N3, N1 + 1);

    if(stmt){
	    patchList(stmt->breakList, nextQuadLabel());
	    patchList(stmt->contList, N1 + 1);
    }
}

stmt_t* HANDLE_BREAK(int lineno) {
	stmt_t *temp = malloc(sizeof(stmt_t));

	make_stmt(temp);
	temp->breakList = newList(nextQuadLabel());
	emit(jump, NULL, NULL, NULL, 0, lineno);
	return temp;
}

stmt_t* HANDLE_CONTINUE(int lineno) {
	stmt_t *temp = malloc(sizeof(stmt_t));

	make_stmt(temp);
	temp->contList = newList(nextQuadLabel());
	emit(jump, NULL, NULL, NULL, 0, lineno);
	return temp;
}
