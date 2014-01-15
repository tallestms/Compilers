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

void printRelationship(int *varRelations, int currentRelationPos)
{
  int i = 0;
  printf("Imprimindo vetor de relacoes.\n");
  for(i=0;i<currentRelationPos;i++)
  {
    printf("%d\n",varRelations[i]);
  }
}