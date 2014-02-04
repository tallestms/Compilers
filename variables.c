#include "variables.h"
#include "hash.h"

variable* createVariable()
{
  variable *newVar;
  if((newVar = ((variable *) malloc (sizeof(variable)))) == NULL)
    return NULL;
  else
    return newVar;
}

void setVariable(variable* var, char* name, char* scope, int type, int matrix, int dimension, int colum, int line)
{
  if (var == NULL)
  {
    printf("Null variable.");
    exit(1);
  }
  else
  {
    strcpy(var->name, name);
    strcpy(var->scope, scope);
    var->type = type;
    var->used = 0;    
    var->matrix = matrix;
    var->dimension = dimension;
    var->nColum = colum;
    var->nLine = line;
  }
}

  /*
   * type 0 = inteiro
   * type 1 = caracter 
   * type 2 = literal
   * type 3 = real
   * type 4 = lógico
   */
int convertType(char *type)
{
  if(strcmp(type, "inteiro")==0)
    return 0;
  else if(strcmp(type, "caracter")==0)
    return 1;
  else if(strcmp(type, "literal")==0)
    return 2;
  else if(strcmp(type, "real")==0)
    return 3;
  else if(strcmp(type, "lógico")==0)
    return 4;
  else
  {
    printf("Crazy thing in converting type: %s\n", type);
    exit(1);
  }
}

void verifyUsed(hashTable *hashtable)
{
    int i;
    List *list, *temp;

    if (hashtable==NULL) 
      return;

    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    printf("Tabela de uso:\n");
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            printf("%s -> %d\n",((variable*)(temp->info))->name,((variable*)(temp->info))->used); 
        }
    }
}

void verifyMatrix(hashTable *hashtable)
{
    int i;
    List *list, *temp;

    if (hashtable==NULL) 
      return;

    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    printf("Tabela de uso:\n");
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            printf("%s -> %d -> %d\n",((variable*)(temp->info))->name,((variable*)(temp->info))->matrix,((variable*)(temp->info))->type); 
        }
    }
}
