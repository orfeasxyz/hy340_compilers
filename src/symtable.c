#include "../include/symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define MIN_SIZE 20
#define MAX_SIZE 2560
#define HASH_MULTIPLIER 65599

char* enum_to_s[] = {
    "VAR_GLOBAL",
    "VAR_LOCAL",
    "VAR_FORMAL",
    "USERFUNC",
    "LIBFUNC"
}; 

int sizes[] = {MIN_SIZE, 40, 80, 160, 320, 640, 1280, MAX_SIZE};

/* Return a hash code for key. */
static unsigned int SymTable_hash(const char *key, size_t max_size){
    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; key[ui] != '\0'; ui++)
        uiHash = uiHash * HASH_MULTIPLIER + key[ui];
    return uiHash % max_size;
}

typedef struct List* List_T;

struct List {
    char* key;
    SymbolTableEntry* val;
    struct List* next;
};

struct SymTable{
    size_t max_size;
    size_t length;
    List_T *buckets;
    struct SymTable* next;
    struct SymTable* prev;
};

/* ================================================= */

size_t get_size(size_t max_size){
	int index = 0;
	for(int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
		if(sizes[i] == max_size) {
			index = i + 1;
			break;
		}
	}
	assert(index);
    return sizes[(index <= 7 ? index : 7)];
}

SymTable_T SymTable_new(void){
    SymTable_T table = malloc(sizeof(struct SymTable));

    table->length = 0;
    table->max_size = MIN_SIZE;
    table->buckets = calloc(table->max_size, sizeof(List_T));
    table->next = NULL;
    table->prev = NULL;

    return table;
}

/* ================================================= */

void SymTable_free(SymTable_T oSymTable){
    List_T temp;
    List_T prev;
    SymTable_T prev_table;
    size_t i;
    if(!oSymTable) return;

    while(oSymTable){
        for(i = 0; i < oSymTable->max_size; i++){
            temp = oSymTable->buckets[i];
            while(temp){
                prev = temp;
                temp = temp->next;
                free(prev->key);
                free(prev->val);
                free(prev);
            }
        }
        prev_table = oSymTable;
        oSymTable = oSymTable->next;
        free(prev_table->buckets);
        free(prev_table);
        prev_table = NULL;
    }

    
    return;
}

/* ================================================= */

unsigned int SymTable_getLength(SymTable_T oSymTable){ 
    assert(oSymTable);
    return oSymTable->length;
}

/* ================================================= */

void rehash(SymTable_T table){
    size_t i;
    List_T prev_node;
    List_T temp;
    List_T* prev_buckets = table->buckets;
    size_t prev_size = table->max_size;

    if(table->max_size == MAX_SIZE) return;

    table->max_size = get_size(table->max_size);
    table->buckets = calloc(table->max_size, sizeof(List_T));
    table->length = 0;

    for(i = 0; i < prev_size; i++){
        temp = prev_buckets[i];
        while(temp){
            SymTable_insert(table, temp->key, temp->val);
            prev_node = temp;
            temp = temp->next;
            free(prev_node->key);
            free(prev_node);
        }
    }

    free(prev_buckets);

    table->length++;
}


SymbolTableEntry* SymTable_insert(SymTable_T oSymTable, const char *key, SymbolTableEntry* value){
    List_T new;
    size_t pos;
    assert(oSymTable);
    assert(key);

    oSymTable->length++;

    if(oSymTable->length > oSymTable->max_size) rehash(oSymTable);

    pos = SymTable_hash(key, oSymTable->max_size);

    new = malloc(sizeof(struct List));
    new->key = malloc(sizeof(key) + 1);
    strcpy(new->key, key);
    new->val = value;

    if(!oSymTable->buckets[pos]){
        new->next = NULL;
        oSymTable->buckets[pos] = new;
    }
    else{
        new->next = oSymTable->buckets[pos];
        oSymTable->buckets[pos] = new;
    }

    return new->val;
}

/* ================================================= */

void SymTable_hide(SymTable_T oSymTable){
    List_T temp;
    size_t i;
    assert(oSymTable);

    for(i = 0; i < oSymTable->max_size; i++){
        temp = oSymTable->buckets[i];
        while(temp){
            temp->val->isActive = 0;
            temp = temp->next;
        }
    }

    return;
}

/* ================================================= */

SymbolTableEntry* SymTable_lookup(SymTable_T oSymTable, const char *key){
    List_T temp;
    SymTable_T current = oSymTable;
    assert(oSymTable);
    assert(key);

    while(current){
        temp = current->buckets[SymTable_hash(key, current->max_size)];

        while(temp){
            if(!strcmp(temp->key, key) && temp->val->isActive) return temp->val;
            temp = temp->next;
        }

        current = current->prev;
    }

    return NULL;
}

SymbolTableEntry* SymTable_lookup_here(SymTable_T oSymTable, const char *key){
    List_T temp;
    assert(oSymTable);
    assert(key);

    temp = oSymTable->buckets[SymTable_hash(key, oSymTable->max_size)];

    while(temp){
        if(!strcmp(temp->key, key) && temp->val->isActive) return temp->val;
        temp = temp->next;
    }

    return NULL;
}

/* ================================================= */

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *key, SymbolTableEntry* value, void *pvExtra), void *pvExtra){
    List_T temp;
    size_t i;
    assert(oSymTable);
    assert(pfApply);

    for(i = 0; i < oSymTable->max_size; i++){
        temp = oSymTable->buckets[i];
        while(temp){
            pfApply(temp->key, temp->val, pvExtra);
            temp = temp->next;
        }
    }
}

/* ================================================= */

void SymTable_next(SymTable_T oSymTable){
    assert(oSymTable);
    if(oSymTable->next){
        oSymTable = oSymTable->next;
        return;
    }

    oSymTable->next = SymTable_new();
    oSymTable->next->prev = oSymTable;
    oSymTable = oSymTable->next;
    
    return;
}

/* ================================================= */

void SymTable_prev(SymTable_T oSymTable){
    assert(oSymTable);
    assert(oSymTable->prev);
    
    oSymTable = oSymTable->prev;
    return;
}

/* ================================================= */

void SymTable_print(SymTable_T oSymTable){
    List_T temp;
    size_t i;
    unsigned int scope = 0;
    if(!oSymTable) return;

    while(oSymTable){
        printf("SCOPE %d \n\n", scope++);
        for(i = 0; i < oSymTable->max_size; i++){
            temp = oSymTable->buckets[i];
            while(temp){
                printf("Key: %s, Val: %s\n", temp->key, enum_to_s[temp->val->type]);
                temp = temp->next;
            }
        }
        oSymTable = oSymTable->next;
        printf("\n\n");
    }

    return;
}