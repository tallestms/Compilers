#ifndef HASH_H_
#define HASH_H_

#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashTable_t {
    int size;       /* the size of the table */
    List **table; /* the table elements */
}; 
typedef struct hashTable_t hashTable;

hashTable *createHash(int size);
unsigned int hash(hashTable *hashtable, char *str);
List *lookupString(hashTable *hashtable, char *str);
int addString(hashTable *hashtable, char *str);
void freeTable(hashTable *hashtable);

#endif /* HASH_H_ */