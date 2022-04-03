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

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, SymbolTableEntry* pvValue, void *pvExtra),const void *pvExtra);