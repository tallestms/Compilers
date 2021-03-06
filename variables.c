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


void setVariable(variable* var, char* name, char* scope, int type, int matrix, int dimension, int column, int line)
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
    var->nColumn = column;
    var->nLine = line;
    var->value = NULL;
    if(!matrix) //nao e matriz
    {
      if(type == 0) //inteiro
      {
	int *value = (int*) malloc (sizeof(int));
	var->value = value;
      }     
      if(type == 3) //reais serao convertidos em double 
      {
	double *value = (double*) malloc(sizeof(double));
	var->value = value;
      }
      if(type == 1) //tipo caracter
      {
	char *value = (char*) malloc(sizeof(char));
	var->value = value;
      }    
      if(type == 2) //tipo literal 
      {
	char *value = (char*) malloc(50*sizeof(char)); //45 e o limite do literal
	var->value = value;
      }
      if(type == 4) //tipo logico -> sera convertido em inteiro (1 ou 0) de acordo com C 
      {
	int *value = (int*) malloc(sizeof(int));
	var->value = value;
      }
    }
    else if(matrix)
    {
      if(dimension==1)
      {
	if(type == 0) //inteiro
	{
	  int *value = (int*) malloc (column*sizeof(int));
	  var->value = value;
	}     
	if(type == 3) //reais serao convertidos em double 
	{
	  double *value = (double*) malloc(column*sizeof(double));
	  var->value = value;
	}
	if(type == 1) //tipo caracter
	{
	  char *value = (char*) malloc(column*sizeof(char));
	  var->value = value;
	}    
	if(type == 2) //tipo literal 
	{
	  char *value = (char*) malloc(column*MAX_LITERAL_DECLARATION*sizeof(char)); //50 e o limite do literal
	  var->value = value;
	}
	if(type == 4) //tipo logico -> sera convertido em inteiro (1 ou 0) de acordo com C 
	{
	  int *value = (int*) malloc(column*sizeof(int));
	  var->value = value;
	}
      }
      else if(dimension==2)
      {
	if(type == 0) //inteiro
	{
	  int *value = (int*) malloc (line*column*sizeof(int));
	  var->value = value;
	}     
	if(type == 3) //reais serao convertidos em double 
	{
	  double *value = (double*) malloc(line*column*sizeof(double));
	  var->value = value;
	}
	if(type == 1) //tipo caracter
	{
	  char *value = (char*) malloc(line*column*sizeof(char));
	  var->value = value;
	}    
	if(type == 2) //tipo literal 
	{
	  char *value = (char*) malloc(line*column*50*sizeof(char)); //45 e o limite do literal
	  var->value = value;
	}
	if(type == 4) //tipo logico -> sera convertido em inteiro (1 ou 0) de acordo com C 
	{
	  int *value = (int*) malloc(line*column*sizeof(int));
	  var->value = value;
	}
      }
    }
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
    return 6; //Tipo em que aceita qualquer tipo de variavel.
  }
}

void convertTypeReverse(int type, char *aux)
{
  if(type==0)
    strcpy(aux, "inteiro");
  else if(type==1)
    strcpy(aux, "caracter");
  else if(type==2)
    strcpy(aux, "literal");
  else if(type==3)
    strcpy(aux, "real");
  else if(type==4)
    strcpy(aux, "lógico");
}

void convertTypeReverseUpper(int type, char *aux)
{
  if(type==0)
    strcpy(aux, "INTEIRO");
  else if(type==1)
    strcpy(aux, "CARACTER");
  else if(type==2)
    strcpy(aux, "LITERAL");
  else if(type==3)
    strcpy(aux, "REAL");
  else if(type==4)
    strcpy(aux, "LOGICO");
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
    //printf("Tabela de uso:\n");
    for(i=0; i<hashtable->size; i++) {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
	    if(((variable*)(temp->info))->used == 0 && ((variable*)(temp->info))->matrix == 0)
	    {
	      char* varAux;
	      char varAux2[100];
	      strcpy(varAux2,((variable*)(temp->info))->name);
	      varAux = strtok(varAux2, " ");
	      printf("Aviso: Variavel %s nao foi utilizada durante o programa", ((variable*)(temp->info))->name);
	      if(varAux = (strtok(NULL, " ")))
		printf(" na funcao %s.\n", varAux);
	      else
		printf(".\n");
	    }
            //printf("%s -> %d\n",((variable*)(temp->info))->name,((variable*)(temp->info))->used); 
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
