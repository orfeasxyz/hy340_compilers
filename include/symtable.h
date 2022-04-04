#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#include "structs.h"

typedef struct SymTable* SymTable_T;

SymTable_T SymTable_new(void);

void SymTable_next(SymTable_T oSymTable);

void SymTable_prev(SymTable_T oSymTable);

void SymTable_free(SymTable_T oSymTable);

unsigned int SymTable_getLength(SymTable_T oSymTable);

void SymTable_insert(SymTable_T oSymTable, const char *pcKey, SymbolTableEntry* pvValue);

void SymTable_hide(SymTable_T oSymTable);

SymbolTableEntry* SymTable_lookup(SymTable_T oSymTable, const char *pcKey);

SymbolTableEntry* SymTable_lookup_here(SymTable_T oSymTable, const char *key);

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, SymbolTableEntry* pvValue, void *pvExtra),const void *pvExtra);

#endif // _SYMTABLE_H_