#include "../include/structs.h"
#include "../include/symtable.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned	scope = 0;
unsigned	anon_count = 0;
quad*		quads = (void*)0; // quad vector
unsigned	total = 1;
unsigned	currQuad = 1;

void expand (void) {
    assert(total == currQuad);
    quad *p = malloc(NEW_SIZE);
    if (quads) {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit (
        iopcode        op,
        Expr*        arg1,
        Expr*        arg2,
        Expr*        result,
        unsigned    label,
        unsigned    line
) {
    // If the vector of quad is full, expand length
    if (currQuad == total) {
        expand();
    }

    // Consturct new quad
    quad* p		= quads + currQuad++;
    p->arg1		= arg1;
    p->arg2		= arg2;
    p->result	= result;
    p->label	= label;
    p->line		= line;
	p->op		= op;
}

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
unsigned tempCounter = 0;
unsigned loopCounter = 0;
unsigned funcCounter = 0;

void makeBoolStmt(Expr* e, int lineno){
    if(e->type == boolexpr_e){
        patchList(e->trueList, nextQuadLabel());
        emit(assign, newExprConstBool(1), NULL, e, 0, lineno);
        emit(jump, NULL, NULL, NULL, nextQuadLabel() + 2, lineno);
        patchList(e->falseList, nextQuadLabel());
        emit(assign, newExprConstBool(0), NULL, e, 0, lineno);
    }
}


void notBoolExpr(Expr* expression, int lineno){
    expression->trueList = newList(nextQuadLabel());
    expression->falseList = newList(nextQuadLabel() + 1);
    emit(if_eq, expression, newExprConstBool(1), NULL, 0, lineno);
    emit(jump, NULL, NULL, NULL, 0, lineno);
}

void checkShort(Expr* e, iopcode op, int lineno){
    if (e->type == var_e ||  e->type == assignexpr_e){
        notBoolExpr(e, lineno);
        patchList((op == and ? e->trueList : e->falseList), nextQuadLabel());
    }

    return;
}

ScopeSpace currScopeSpace(void){
    if(scopeSpaceCounter == 1){
        return programvar;
    }

    if(scopeSpaceCounter % 2 == 0){
        return formalarg;
    }

    return functionlocal;
}

unsigned currScopeOffset (void) { 
    switch (currScopeSpace ()) {
        case programvar: 
            return programVarOffset; 
        case functionlocal:
            return functionLocalOffset;
        case formalarg: 
            return formalArgOffset;
        default:
            assert (0);
    }
}

void incCurrScopeOffset(void){ 
    switch (currScopeSpace()) {
        case programvar: 
            ++programVarOffset; 
            break; 
        case functionlocal: 
            ++functionLocalOffset;
            break; 
        case formalarg: 
            ++formalArgOffset; 
            break; 
        default: 
            assert (0);
    }
}

void enterScopeSpace (void){
    ++scopeSpaceCounter;
}

void exitScopeSpace (void){ 
    assert(scopeSpaceCounter>1); 
    --scopeSpaceCounter; 
}

void resetFormalArgsOffset(void){
    formalArgOffset = 0;
}

void resetFunctionLocalOffset(void){
    functionLocalOffset = 0;
}

void restoreCurrScopeOffset(unsigned n){
    switch(currScopeSpace()){
        case programvar:    programVarOffset = n; break;
        case functionlocal: functionLocalOffset = n; break;
        case formalarg:     formalArgOffset = n; break;
        default:            assert(0);
    }
}

unsigned nextQuadLabel(void){
    return currQuad;
}

void patchLabel(unsigned quadNo, unsigned label){
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

char* newTempName(){
    int count = 0, num = tempCounter;
	while (num) {
		num /= 10;
		++count;
	}

    char* tempName = malloc(count + 3);

    sprintf(tempName, "_t%d", tempCounter++);

    return tempName;
}

void resetTemp() {tempCounter = 0;}

SymbolTableEntry* newTemp(int lineno){
    char* name = newTempName();
    SymbolTableEntry* sym = SymTable_lookup(current_table, name);
    if(sym) return sym;
    SymbolTableEntry* temp;
    temp = makeSymbol(name, lineno, scope);
    temp->type = (scope ? VAR_LOCAL : VAR_GLOBAL);
    temp->space = currScopeSpace();
    temp->offset = currScopeOffset();
    incCurrScopeOffset();
    return temp;
}

Expr* newExpr(ExprType t){
    Expr* e = (Expr*) malloc(sizeof(Expr));
    memset(e, 0, sizeof(Expr));
    e->type = t;
    return e;
}

Expr* newExprConstString(char* s){
    Expr* e = newExpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

Expr* newExprConstNum(double i){
    Expr* e = newExpr(constnum_e);
    e->numConst = i;
    return e;
}

Expr* newExprConstBool(unsigned char boolean){
    Expr* e = newExpr(constbool_e);
    e->boolConst = !!boolean;
    return e;
}

SymbolTableEntry* makeSymbol(char* key, int lineno, int scope){
    SymbolTableEntry* temp = calloc(1, sizeof(SymbolTableEntry));
    temp->isActive = 1;
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;
    temp->returnList = 0;

    return temp;
}

void make_stmt(stmt_t *s) {
	s->breakList = s->contList = 0;
}

int newList(int i ) {
    if (currQuad == total) {
        expand();
    }
	quads[i].label = 0;
	return i;
}

int mergeList(int l1, int l2) {
	if(!l1) {
		return l2;
	}
	else if(!l2) {
		return l1;
	}
	else {
		int i = l1;
		while (quads[i].label) {
			i = quads[i].label;
		}
		quads[i].label = l2;
		return l1;
	}
	return 0; // dummy return to avoid warning
}

void patchList(int list, int label) {
	while (list) {
		int next = quads[list].label;
		quads[list].label = label;
		list = next;
	}
}

void checkArith(Expr* e, const char* context){
    if (e->type == constbool_e ||
        e->type == conststring_e ||
        e->type == nil_e ||
        e->type == newtable_e ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e )
    fprintf(stderr,"Illegal expr used in %s!", context);
}

int boolVal(Expr *e) {
    switch (e->type) {
        case constbool_e:
            return e->boolConst;
        case constnum_e:
            return e->numConst != 0;
        case conststring_e:
            return strlen(e->strConst) != 0;
        case nil_e:
            return 0;
        case tableitem_e:
            return 1;
        case programfunc_e:
            return 1;
        case libraryfunc_e:
            return 1;
        case newtable_e:
            return 1;
        default:
            assert(0);
    }
}

char* getStringValueQuad(Expr* e){
    switch(e->type){
        case conststring_e:{
            char* str = malloc(sizeof(char) * (strlen(e->strConst) + 3));
            sprintf(str, "\"%s\"", e->strConst);
            return str;
        }
        case constnum_e:{
            char* str = malloc(sizeof(char) * 32);
            sprintf(str, "%.1f", e->numConst);
            return str;
        }
        case nil_e:
            return "nil";
        case tableitem_e:
            return e->sym->name;
        case programfunc_e:
            return e->sym->name;
        case libraryfunc_e:
            return e->sym->name;
        case boolexpr_e:
            return e->sym->name;
        case arithmexpr_e:{
            return e->sym->name;
        }
        case newtable_e:
            return e->sym->name;
        case constbool_e:
            return e->boolConst ? "true" : "false";
        case var_e:
            return e->sym->name;
        case assignexpr_e:
            return e->sym->name;
        default: assert(0);
    }
}

const char* str_iopcodeName[] = {
    "assign",
	"jump",
    "mul",
    "uminus",
    "not",
    "if_lesseq",
    "if_greater",
    "ret",
    "funcend",
    "tablegetelem",
    "add",
    "mydiv",
    "and",
    "if_eq",
    "if_geatereq",
    "call",
    "getretval",
    "tablecreate",
    "tablesetelem",
    "sub",
    "mod",
    "or",
    "if_noteq",
    "if_less",
    "param",
    "funcstart"
};

int isBranch(iopcode op) {
	switch(op) {
		case jump:
		case if_lesseq:
		case if_greater:
		case if_eq:
		case if_geatereq:
		case if_noteq:
		case if_less:
			return 1;
		default:
			return 0;
	}
	return 0;
}

const char* iopcodeName(quad* q){
    return str_iopcodeName[q->op];
}

void printQuads(void) {
	char str_label[16] = {0};
	printf("%8s | %14s | %10s | %10s | %10s | %10s | %10s |\n", "quad#", "opcode", "result", "arg1", "arg2", "label", "line");
    for (int i = 1; i < currQuad; i++) {
        quad* q = &quads[i];

		if (isBranch(q->op)) {
			sprintf(str_label, "%d", q->label);
		}
		else {
			strcpy(str_label, " ");
		}

        printf("%8d | %14s | %10s | %10s | %10s | %10s | %10d |\n",
        i,
        iopcodeName(q),
        (q->result != NULL ? getStringValueQuad(q->result) : " "),
        (q->arg1 != NULL ? getStringValueQuad(q->arg1) : " "),
        (q->arg2 != NULL ? getStringValueQuad(q->arg2) : " "),
        str_label,
        q->line);
    }
}
