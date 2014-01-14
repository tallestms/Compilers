#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lists.h"

struct variable_t {
  char name[50]; 
  char scope[50];
  char type[10];
  void *value;
  int used;
};
typedef struct variable_t variable;

/*
 * Aloca memoria para variavel
 * Input: nada
 * Output: ponteiro para variavel
 */
variable* createVariable();

/*
 * Inicializa variavel e seu conteudo
 * Input: ponteiro para variavel e seus atributos(nome, escopo e etc)
 * Output: nada
 */
void setVariable(variable* var, char* name, char* scope, char* type, void* value);

#endif /* VARIABLES_H_ */
