#include "hash.h"

hashTable *createHash(int size)
{
    hashTable *newTable;
    
    if (size<1) return NULL; /* invalid size for table */

    if ((newTable = malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }
    
    if ((newTable->table = malloc(sizeof(List *) * size)) == NULL) {
        return NULL;
    }
  
    int i;
    for(i=0; i<size; i++) 
      newTable->table[i] = NULL;

    newTable->size = size;

    return newTable;
}

unsigned int hash(hashTable *hashtable, char *str)
{
    unsigned int hashval;
    
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
        if (strcmp(str, (char*)(((variable*)(list->info))->name)) == 0){ return list;}
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


    if ((newList = malloc(sizeof(List))) == NULL) return 1;

    currentList = lookupStringVariable(hashtable, str);
    
    if (currentList != NULL)
      return 1;
    
    /* insert into list */
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

    if ((newList = malloc(sizeof(List))) == NULL) return 1;

    currentList = lookupStringFunction(hashtable, str);
    
    if (currentList != NULL)
      return 1;
    
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


    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
	    //if(temp->info!=NULL)
	    {
	      //if(((variable*)(temp->info))->value!=NULL)
		//free(((variable*)(temp->info))->value);
	      //free(temp->info);
	    }
	    if(temp!=NULL)
	      free(temp);
        }
    }

    //free(hashtable->table);
    //free(hashtable);
}

void freeTableFunction(hashTable *hashtable)
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
	    if(temp->info!=NULL)
	    {
	      if(((List*)((function*)temp->info)->parameters)!=NULL)
	      {
		destroyList(((List*)((function*)temp->info)->parameters));
	      }
	      free(temp->info);
	    }
            free(temp);
        }
    }

    /* Free the table itself */
    //free(hashtable->table);
    //free(hashtable);
}
