#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

struct function_t
{
  char name[50];
  int returnType;
  int arity;
  List* parameters;
  int lineUsed;
  List* nextFunction;
  int functionDeclared;
};
typedef struct function_t function;

  /*
   * returnType 0 = inteiro
   * returnType 1 = caracter 
   * returnType 2 = string
   * returnType 3 = real
   * returnType 4 = booleano
   */

function* createFunction();
void setFunction(function *newFunc, char* name, int returnType, int arity, List* parameters, int lineUsed, List* nextFunction, int functionDeclared);

#endif /*FUNCTIONS_H_*/