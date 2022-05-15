#include "../include/structs.h"
#include "../include/symtable.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned	scope = 0;
unsigned	anon_count = 0;
quad*		quads = (void*)0; // quad vector
unsigned	total = 0;
unsigned	currQuad = 0;

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
    quad* p        = quads + currQuad++;
    p->arg1        = arg1;
    p->arg2        = arg2;
    p->result    = result;
    p->label    = label;
    p->line        = line;
}

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
unsigned tempCounter = 0;

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
    while(num){
        num /= 10;
        count++;
    }

    char* tempName = malloc(count + 3);

    sprintf(tempName, "_t%d", tempCounter);

    return tempName;
}

void resetTemp() {tempCounter = 0;}

SymbolTableEntry* newTemp(){
    char* name = newTempName();
    SymbolTableEntry* sym = SymTable_lookup(current_table, name);
    if(sym) return sym;
    return makeSymbol(name, 0, scope);
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

SymbolTableEntry* makeSymbol(char* key, int lineno, int scope){
    SymbolTableEntry* temp = malloc(sizeof(SymbolTableEntry));
    temp->isActive = 1;
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;

    return temp;
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
        case arithmexpr_e:
            return e->numConst != 0;
        case boolexpr_e:
            return e->boolConst;
        case programfunc_e:
            return 1;
        case libraryfunc_e:
            return 1;
        default:
            assert(0);
    }
}

char* getStringValueQuad(Expr* e){
    switch(e->type){
        case conststring_e:
            return e->strConst;
        case constnum_e:{
            char* str = malloc(sizeof(char) * 32);
            sprintf(str, "%f", e->numConst);
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
            char* str = malloc(sizeof(char) * 32);
            sprintf(str, "%f", e->numConst);
            return str;
        }
        case newtable_e:
            return "table";
        case constbool_e:
            return e->boolConst ? "true" : "false";
        case var_e:
            return e->sym->name;
        case assignexpr_e:
            return "assignexpr";
        default: assert(0);
    }
}

char* iopcodeName(quad* quad){
    switch (quad->op)
    {
        case assign: return "assign";
        case mul: return "mul";
        case uminus: return "uminus";
        case not: return "not";
        case if_lesseq: return "if_lesseq";
        case if_greater: return "if_greater";
        case ret: return "ret";
        case funcend: return "funcend";
        case tablegetelem: return "tablegetelement";
        case add: return "add";
        case mydiv: return "mydiv";
        case and: return "and";
        case if_eq: return "if_eq";
        case if_geatereq: return "if_geatereq";
        case call: return "call";
        case getretval: return "getretval";
        case tablecreate: return "tablecreate";
        case sub: return "sub";
        case mod: return "mod";
        case or: return "or";
        case if_noteq: return "if_noteq";
        case if_less: return "if_less";
        case param: return "param";
        case funcstart: return "funcstart";
        default: assert(0);
    }
}

void printQuads(void) {
    printf("quad# |  opcode   |  result  | arg1  |  arg2  |  label  |\n");
    for (int i = 0; i < currQuad; i++) {
        quad* q = &quads[i];
        printf("%4d | %10s | %10s | %10s | %10s | %10d |\n",
        i,
        iopcodeName(q),
        (q->result != NULL ? getStringValueQuad(q->result) : " "),
        (q->arg1 != NULL ? getStringValueQuad(quads->arg1) : " "),
        (quads->arg2 != NULL ? getStringValueQuad(quads->arg2) : " "),
        q->label ? q->label : 0);
    }
}