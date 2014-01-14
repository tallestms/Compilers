#include "variables.h"

variable* createVariable()
{
  variable *newVar;
  if((newVar = ((variable *) malloc (sizeof(variable)))) == NULL)
    return NULL;
  else
    return newVar;
}

void setVariable(variable* var, char* name, char* scope, char* type, void* value)
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
    strcpy(var->type, type);
    var->value = value;
    var->used = 0;    
  }
}