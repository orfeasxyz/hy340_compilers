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

SymbolTableEntry* makeSymbol(char* key, int lineno, int scope){
    SymbolTableEntry* temp = malloc(sizeof(SymbolTableEntry));
    temp->isActive = 1;
    temp->name = malloc(sizeof(key) + 1);
    strcpy(temp->name, key);
    temp->line = lineno;
    temp->scope = scope;

    return temp;
}