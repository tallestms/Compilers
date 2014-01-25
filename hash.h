#ifndef HASH_H_
#define HASH_H_

#include "lists.h"
#include "variables.h"
#include "functions.h"
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
List *lookupStringVariable(hashTable *hashtable, char *str);
List *lookupStringFunction(hashTable *hashtable, char *str);
int addInfoVariable(hashTable *hashtable, char*str, void *info);
int addInfoFunction(hashTable *hashtable, char*str, void *info);
void freeTable(hashTable *hashtable);
void freeTableFunction(hashTable *hashtable);

#endif /* HASH_H_ */
