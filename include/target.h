#ifndef _TARGET_H_
#define _TARGET_H_

#include "structs.h"

unsigned consts_newstring(char*);
unsigned consts_newnumber(double);
unsigned newused(char*);
unsigned newfunc(SymbolTableEntry*);
// new oeparant func ...

void generate_ADD(quad*);
void generate_SUB(quad*);
void generate_MUL(quad*);
void generate_DIV(quad*);
void generate_MOD(quad*);
void generate_NEWTABLE(quad*);
void generate_TABLEGETELEM(quad*);
void generate_TABLESETELEM(quad*);   
void generate_ASSIGN(quad*);
void generate_NOP(quad*);
void generate_JUMP(quad*);
void generate_IF_EQ(quad*);
void generate_IF_NOTEQ(quad*);
void generate_IF_GREATER(quad*);
void generate_IF_GREATEREQ(quad*);
void generate_IF_LESS(quad*);
void generate_IF_LESSEQ(quad*);
void generate_NOT(quad*);
void generate_OR(quad*);
void generate_AND(quad*);
void generate_PARAM(quad*);
void generate_CALL(quad*);
void generate_GETRETVAL(quad*);
void generate_FUNCSTART(quad*);
void generate_RETURN(quad*);
void generate_FUNCEND(quad*);

typedef void (*generate_func_t)(quad*);

generate_func_t generators[] = {
    generate_ASSIGN,
    generate_JUMP,
    generate_MUL,
    generate_NOP,
    generate_NOT,
    generate_IF_LESSEQ,
    generate_IF_GREATER,
    generate_RETURN,
    generate_FUNCEND,
    generate_TABLEGETELEM,
    generate_ADD,
    generate_DIV,
    generate_AND,
    generate_IF_EQ,
    generate_IF_GREATEREQ,
    generate_CALL,
    generate_GETRETVAL,
    generate_NEWTABLE,
    generate_TABLESETELEM,
    generate_SUB,
    generate_MOD,
    generate_OR,
    generate_IF_NOTEQ,
    generate_IF_LESS,
    generate_PARAM,
    generate_FUNCSTART
};

void generate(void);

#endif _TARGET_H_
