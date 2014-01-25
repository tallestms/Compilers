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

void setFunction(function *newFunc, char* name, int returnType, int arity, List* parameters, int functionDeclared)
{
  if(!newFunc)
  {
    printf("Erro em funcao.\n");
    exit(1);
  }
  else
  {
    strcpy(newFunc->name,name);
    newFunc->returnType = returnType;
    newFunc->arity = arity;
    newFunc->parameters = parameters;
    newFunc->functionDeclared = functionDeclared;
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
}