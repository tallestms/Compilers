#include "hash.h"

hashTable *createHash(int size)
{
    hashTable *newTable;
    
    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((newTable = malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }
    
    /* Attempt to allocate memory for the table itself */
    if ((newTable->table = malloc(sizeof(List *) * size)) == NULL) {
        return NULL;
    }
  
    int i;
    /* Initialize the elements of the table */
    for(i=0; i<size; i++) 
      newTable->table[i] = NULL;

    /* Set the table's size */
    newTable->size = size;

    return newTable;
}

unsigned int hash(hashTable *hashtable, char *str)
{
    unsigned int hashval;
    
    /* we start our hash out at 0 */
    hashval = 0;

    /* this is a faster operation than multiplication: 32 -1 = 31 */
    for(; *str != '\0'; str++) 
      hashval = *str + (hashval << 5) - hashval;

    return hashval % hashtable->size;
}

List *lookupStringVariable(hashTable *hashtable, char *str)
{
    List *list;
    unsigned int hashval = hash(hashtable, str);

    for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, (char*)(((variable*)(list->info))->name)) == 0) return list;
    }
    return NULL;
}

List *lookupStringFunction(hashTable *hashtable, char *str)
{
    List *list;
    unsigned int hashval = hash(hashtable, str);

    for(list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (strcmp(str, (char*)(((function*)(list->info))->name)) == 0) return list;
    }
    return NULL;
}

int addInfoVariable(hashTable *hashtable, char*str, void *info)
{
    List *newList;
    List *currentList;
    unsigned int hashval = hash(hashtable, str);

    /* Attempt to allocate memory for list */
    if ((newList = malloc(sizeof(List))) == NULL) return 1;

    /* Does item already exist? */
    currentList = lookupStringVariable(hashtable, str);
    
    /* item already exists, don't insert it again. */
    if (currentList != NULL)
      return 1;
    
    /* insert into list */
    char *strTemp = malloc(sizeof(str));
    strcpy(strTemp, str);
    newList->info = info;
    newList->next = hashtable->table[hashval];
    hashtable->table[hashval] = newList;

    return 0;
}

int addInfoFunction(hashTable *hashtable, char*str, void *info)
{
    List *newList;
    List *currentList;
    unsigned int hashval = hash(hashtable, str);

    /* Attempt to allocate memory for list */
    if ((newList = malloc(sizeof(List))) == NULL) return 1;

    /* Does item already exist? */
    currentList = lookupStringFunction(hashtable, str);
    
    /* item already exists, don't insert it again. */
    if (currentList != NULL)
      return 1;
    
    /* insert into list */
    char *strTemp = malloc(sizeof(str));
    strcpy(strTemp, str);
    newList->info = info;
    newList->next = hashtable->table[hashval];
    hashtable->table[hashval] = newList;

    return 0;
}

void freeTable(hashTable *hashtable)
{
    int i;
    List *list, *temp;

    if (hashtable==NULL) 
      return;

    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->info);
            free(temp);
        }
    }

    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
}
