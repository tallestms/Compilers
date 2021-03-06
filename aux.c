#include <stdlib.h>
#include <string.h>
#include "aux.h"

extern int err;

int verifyRelationship(int *varRelations, int currentRelationPos)
{
  int i = 0;
  int compare = varRelations[0];
  for(i=0;i<currentRelationPos;i++)
  {
    if(varRelations[i] != compare)
      return 0;
  }
  return 1;
}

int verifyRelationshipComparison(int *varRelations, int currentRelationComparison, int currentRelationPos)
{
  int i = 0;
  int compare = varRelations[currentRelationPos-currentRelationComparison];
    if (compare == 1 || compare == 2)
  { 
    return 0;
  }
  for(i=currentRelationPos-currentRelationComparison;i<currentRelationPos;i++)
  {
    if(varRelations[i] != compare || varRelations[i] == 1 || varRelations[i] == 2)
      return 0;
  }
  return 1;
}

int verifyRelationshipCondition(int *varRelations, int currentRelationComparison, int currentRelationPos)
{
  int i = 0;
  int compare = varRelations[currentRelationPos-currentRelationComparison];
  //printf("Compare: %d\n", compare);
    if (compare == 1 || compare == 2)
  {
    return 0;
  }
  for(i=currentRelationPos-currentRelationComparison;i<currentRelationPos;i++)
  {
    //printf("%d ", varRelations[i]);
    if(varRelations[i] != compare || varRelations[i] == 1 || varRelations[i] == 2)
      return 0;
  }
  return 1;
}

void printRelationship(int *varRelations, int currentRelationPos)
{
  int i = 0;
  printf("Imprimindo vetor de relacoes.\n");
  for(i=0;i<currentRelationPos;i++)
  {
    printf("%d\n",varRelations[i]);
  }
}

int numSpaces(char *s)
{
    int counter = 0;
    int i;
    for (i = 0; s[i]; i++)
    { 
	if(s[i]==' ')
	  counter++;
    }
return counter;
}

int convertValuesTreeNode(char v[50],char t[50]){
	if(!strcmp(t, "LITERAL")) return -2;	
	if(!strcmp(t, "CARACTER")) return -1;	
	if(!strcmp(t, "LOGICO")) return 0;
	if(!strcmp(t, "INTEIRO")) return 1;
	if(!strcmp(t, "REAL")) return 2;
	if(!strcmp(v,":=")) return 3;
	if(!strcmp(v, "/")) return 4;
	if(!strcmp(v, "*")) return 5;
	if(!strcmp(v, "%")) return 6;
	if(!strcmp(v, "+")) return 7;
	if(!strcmp(t, "OPERADOR-UNARIO")) return 8; 
	if(!strcmp(v, "-")) return 9;
	if(!strcmp(t, "VARIAVEL") || !strcmp(t, "IDENTIFICADOR") ) return 10;
	if(!strcmp(v, "()")) return 11;
	if(!strcmp(v, "[]")||!strcmp(v, "{}")) return 12;
	if(!strcmp(t, "MATRIX") )return 13;
	if(!strcmp(v, ">")) return 14;
	if(!strcmp(v, "<")) return 15;
	if(!strcmp(v, "<>")) return 16;
	if(!strcmp(v, "=")) return 17;
	if(!strcmp(v, ">=")) return 18;
	if(!strcmp(v, "<=")) return 19;
	if(!strcmp(v, "e")) return 20;
	if(!strcmp(v, "ou")) return 21;
	if(!strcmp(v,"condicao-enquanto")) return 22;
	if(!strcmp(v,"condicao-faca-enquanto")) return 23;
	if(!strcmp(v,"condicao-se-senao")) return 24;
	if(!strcmp(v,"condicao-se")) return 25;
	if(!strcmp(v,"condicao-para")) return 26;
	if(!strcmp(v,"condicao-seleciona")) return 27;
	if(!strcmp(v, "^")) return 28;
	if(!strcmp(t, "CHAMADA FUNCAO")) return 29;
	if(!strcmp(t,"RETORNO FUNCAO")) return 30; 
	if(!strcmp(v, "maximo")) return 31;
	if(!strcmp(v, "minimo")) return 32;
	if(!strcmp(v, "media")) return 33;
	if(!strcmp(t, "imprima")) return 34;
	if(!strcmp(t, "leia")) return 35;
	if(!strcmp(t, "imprimaln")) return 36;
	if(!strcmp(t, "leialn")) return 37;
	
	
	return -1000;
	
}

double stringRealToDouble(char s[50]){
	char *parte1;
	char *parte2;
	double d;
	int i;
	parte1 = (char*)strtok(s,"e");
	d = (double) atof(parte1);
	parte2 = (char*)strtok(NULL,"e");
	if(parte2!=NULL){
		if( *(parte2) == '-'){
			i = atoi(parte2+1);					
			for(;i>0;i--) d /= 10;
			
		}else{
			i = atoi(parte2);
			for(;i>0;i--) d *= 10;
		}
	}
	
	return d;
}

char getCharFromCharString(char s[50]){
	if( s[1] == '\\' ){
		char ch = s[2];
		switch (ch){
		case 'n':
			return '\n';
		case '0':
			return '\0';
		case '\\':
			return '\\'; 
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		case 'f':
			return '\f';
		case '7':
			return '\7';
		case 'a':
			return '\a';
		case '\'':
			return '\'';
		case '"':
			return '"'; 
		default: 
			return '\0'; 
		}
	}else {
		return s[1];
	}
}

int findArgumentType(int argumentNumber, List* aux)
{
  int i;
  List* aux2 = aux;
  for(i = 1; i < argumentNumber; i++)
  {
    aux2 = aux2->next;
  }
  return ((int)(aux2->info));
  
}

void retiraAspasFinal(char* s){
	int i;
	for(i=0;s[i];i++);
	s[i-1] = '\0';	
}

void *retornaValor(int type, void* point){
	if (point == NULL) return NULL;
	if(type == 0 || type ==4 ){
		int* intReturn = (int*)malloc(sizeof(int));
		*intReturn = *((int*)point);
		return intReturn;
	}
	if(type == 1) {
		char *  charReturn = (char*) malloc(sizeof(char));
		*charReturn = *((char*)point);
		return charReturn;
	}
	if(type == 2) {
		char *  stringReturn = (char*) malloc(53*sizeof(char));
		strcpy(stringReturn,((char*)point));
		return stringReturn;
	}
	if(type == 3){
		double * doubleReturn = (double*)malloc(sizeof(double));
		*doubleReturn = *((double*)point);
		return doubleReturn;
	}
	return;
}

int verifyPrimitivesMaxMinMed(char* currentFunction)
{
  if(strcmp(currentFunction, "maximo inteiro") == 0)
      return 1;
  else if(strcmp(currentFunction, "maximo real") == 0)
      return 1;
  else if(strcmp(currentFunction, "maximo caracter") == 0)
      return 1;
  else if(strcmp(currentFunction, "minimo inteiro") == 0)
      return 1;
  else if(strcmp(currentFunction, "minimo real") == 0)
      return 1;
  else if(strcmp(currentFunction, "minimo caracter") == 0)
      return 1;
  else if(strcmp(currentFunction, "media inteiro") == 0)
      return 1;
  else if(strcmp(currentFunction, "media real") == 0)
      return 1;
  else if(strcmp(currentFunction, "media caracter") == 0)
      return 1;
  else
      return 0;  
}
