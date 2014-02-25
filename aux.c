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

	if(!strcmp(t, "INTEIRO")) return 1;
	if(!strcmp(t, "REAL")) return 2;
	if(!strcmp(v,":=")) return 3;
	if(!strcmp(v, "/")) return 4;
	if(!strcmp(v, "*")) return 5;
	if(!strcmp(v, "%")) return 6;
	if(!strcmp(v, "+")) return 7;
	if(!strcmp(v, "-")) return 8;
	return -1;
	
}


