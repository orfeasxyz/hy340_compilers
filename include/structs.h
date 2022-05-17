#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef enum iopcode { 
    assign, 
    jump,
    mul, 
    uminus, 
    not, 
    if_lesseq, 
    if_greater, 
    ret, 
    funcend, 
    tablegetelem,  
    add, 
    mydiv, //conflict with stdlib.h
    and, 
    if_eq, 
    if_geatereq,
    call,
    getretval, 
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

    //function exlusives
    unsigned iadress;
    unsigned totalLocals;
} SymbolTableEntry;

typedef struct Expr {
	ExprType			type;
	SymbolTableEntry*	sym;
	struct Expr*	    index;
	double			    numConst;
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

typedef struct Call {
    Expr*           elist;
    unsigned char   method;
    char*           name;
} Call;

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

extern unsigned scope;
extern unsigned anon_count;

extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;
extern unsigned scopeSpaceCounter;

extern unsigned tempCounter;

char* newTempName();
void resetTemp();
SymbolTableEntry* newTemp();

SymbolTableEntry* makeSymbol(char*, int, int);
ScopeSpace currScopeSpace(void);
unsigned currScopeOffset(void);
void incCurrScopeOffset(void);
void enterScopeSpace(void);
void exitScopeSpace(void);
void resetFormalArgsOffset(void);
void resetFunctionLocalOffset(void);
void restoreCurrScopeOffset(unsigned);
unsigned nextQuadLabel(void);
void patchLabel(unsigned, unsigned);
Expr* newExpr(ExprType t);
Expr* newExprConstString(char*);
Expr* newExprConstNum(double);
Expr* newExprConstBool(unsigned char b);
void checkArith(Expr*, const char*);
int boolVal(Expr *);
char* getStringValueQuad(Expr*);

extern const char* str_iopcodeName[];
const char* iopcodeName(quad*);
void printQuads(void);


#endif // _STRUCTS_H_
