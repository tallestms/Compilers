#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"
#include "aux.h"

#define T_INTEIRO 0
#define T_CARACTER 1
#define T_LITERAL 2
#define T_REAL 3
#define T_LOGICO 4
#define T_SEMRETORNO 5


struct variable_t {
  char name[50]; 
  char scope[50];
  int type;
  void *value;
  int used;
  int matrix;
  int dimension;
  int nColumn;
  int nLine;
};
typedef struct variable_t variable;

  /*
   * type 0 = inteiro
   * type 1 = caracter 
   * type 2 = literal
   * type 3 = real
   * type 4 = lógico
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
void setVariable(variable* var, char* name, char* scope, int type, int matrix, int dimension, int column, int line);
int convertType(char *type);
int convertTypeRelation(char *type);
void convertTypeReverse(int type, char *aux);
void convertTypeReverseUpper(int type, char *aux);

#endif /* VARIABLES_H_ */
