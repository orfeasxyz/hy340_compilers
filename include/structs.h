#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef enum iopcode { 
    assign, 
    mul, 
    uminus, 
    not, 
    if_lesseq, 
    if_greater, 
    ret, funcend, 
    tablegetelem,  
    add, 
    mydiv, //conflict with stdlib.h
    and, 
    if_eq, 
    if_geatereq,
    call, getretval, 
    tablecreate, 
    tablesetelem,
    sub, 
    mod, 
    or, 
    if_noteq, 
    if_less, 
    param, 
    funcstart
} iopcode;


typedef enum SymbolType {
    VAR_GLOBAL,
    VAR_LOCAL,
    VAR_FORMAL,
    USERFUNC,
    LIBFUNC
} SymbolType;

typedef enum ScopeSpace {
    programvar,
    functionlocal,
    formalarg
} ScopeSpace;

typedef enum ExprType {
	var_e,
	tableitem_e,

	programfunc_e,
	libraryfunc_e,

	arithmexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,

	constnum_e,
	constbool_e,
	conststring_e,

	nil_e
} ExprType;




typedef struct SymbolTableEntry {
    int isActive;
    ScopeSpace space;
    char* name;
    unsigned scope;
    unsigned offset; // scopespace offset
    unsigned line;
    SymbolType type;
} SymbolTableEntry;

typedef struct Expr {
	ExprType			type;
	SymbolTableEntry*	sym;
	struct Expr*	    index;
	double			    numCosnt;
	char*			    strConst;
	unsigned char	    boolConst;

	struct Expr*	    next;
} Expr;

typedef struct quad {
	iopcode	    op;
	Expr*		result;
	Expr*		arg1;
	Expr*		arg2;
	unsigned	label;
	unsigned	line;
} quad;

extern quad*	quads;
extern unsigned	total;
extern unsigned	currQuad;

#define EXPAND_SIZE 1024
#define CURR_SIZE	(total*sizeof(quad))
#define NEW_SIZE	(EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

void expand();
void emit (
	iopcode     op,
	Expr*	    arg1,
	Expr*	    arg2,
	Expr*		result,
	unsigned	label,
	unsigned	line
);

extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;
extern unsigned scopeSpaceCounter;

ScopeSpace currScopeSpace(void);
unsigned currScopeOffset(void);
void incCurrScopeOffset(void);
void enterScopeSpace(void);
void exitScopeSpace(void);

#endif // _STRUCTS_H_
