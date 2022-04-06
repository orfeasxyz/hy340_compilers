#ifndef _STRUCTS_H_
#define _STRUCTS_H_

enum SymbolType {
    VAR_GLOBAL,
    VAR_LOCAL,
    VAR_FORMAL,
    USERFUNC,
    LIBFUNC
}; 

typedef struct Variable {
    char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function {
    char *name;
    unsigned int scope;
    unsigned int line;
} Function; 

typedef struct SymbolTableEntry {
    int isActive;
    union {
        Variable *varVal;
        Function *funcVal;
    } value;

    enum SymbolType type;
} SymbolTableEntry;

#endif // _STRUCTS_H_
