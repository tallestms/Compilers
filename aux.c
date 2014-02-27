#include <stdlib.h>
#include "aux.h"

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
	if(!strcmp(t, "VARIAVEL")) return 10;
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
	//if(!strcmp(v,"condicao-para")) return 26; //TODO
	if(!strcmp(v,"condicao-seleciona")) return 27;
	
	return -1;
	
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
