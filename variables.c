#include "variables.h"

variable* createVariable()
{
  variable *newVar;
  if((newVar = ((variable *) malloc (sizeof(variable)))) == NULL)
    return NULL;
  else
    return newVar;
}

void setVariable(variable* var, char* name, char* scope, int type)
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