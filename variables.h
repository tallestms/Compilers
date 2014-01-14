#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"


struct variable_t {
  char name[50]; 
  char scope[50];
  int type;
  void *value;
  int used;
};
typedef struct variable_t variable;

  /*
   * type 0 = inteiro
   * type 1 = caracter 
   * type 2 = string
   * type 3 = real
   * type 4 = booleano
   */

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
void setVariable(variable* var, char* name, char* scope, int type, void* value);

#endif /* VARIABLES_H_ */