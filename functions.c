#include "functions.h"

function* createFunction()
{
  function* newFunction;
  if((newFunction = (function*) malloc (sizeof(function)))==NULL)
    return NULL;
  else
    return newFunction;
}

void setFunction(function *newFunc, char* name, int returnType, int arity, List* parameters)
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
  }
}
