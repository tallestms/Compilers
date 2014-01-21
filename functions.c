#include "functions.h"
#include "hash.h"

function* createFunction()
{
  function* newFunction;
  if((newFunction = (function*) malloc (sizeof(function)))==NULL)
    return NULL;
  else
    return newFunction;
}

void setFunction(function *newFunc, char* name, int returnType, int arity, List* parameters, int lineUsed, List* nextFunction)
{
  if(!newFunc)
  {
    printf("Null function.");
    exit(2);
  }
  else
  {
    strcpy(newFunc->name,name);
    newFunc->returnType = returnType;
    newFunc->arity = arity;
    newFunc->parameters = parameters;
    newFunc->lineUsed = lineUsed;
    newFunc->nextFunction = NULL;
  }
}

int convertFunctionArgument(char* argumentType, hashTable* hashVariables, int nLine)
{
  if(strcmp(argumentType, "inteiro")==0)
    return 0;
  else if(strcmp(argumentType, "caracter")==0)
    return 1;
  else if(strcmp(argumentType, "literal")==0)
    return 2;
  else if(strcmp(argumentType, "real")==0)
    return 3;
  else if(strcmp(argumentType, "lógico")==0)
    return 4;
  else
  {
    List *identifier_temp = lookupStringVariable(hashVariables, argumentType);
    if(identifier_temp==NULL)
    {
      printf("Variavel nao declarada na linha %d.\n", nLine);
      return 5; //Tipo de erro, o resto da funcao nao sera verificado.
    }
    if(((variable*)(identifier_temp->info))->used==0)
    {
      printf("Variavel %s nao foi inicializada na linha %d.\n", argumentType, nLine);
      return 5; //Tipo de erro, o resto da funcao nao sera verificado.
    }   
    return(((variable*)(identifier_temp->info))->type);
  }
    
}