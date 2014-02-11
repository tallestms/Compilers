#include "lists.h"
#include "tree.h"

treeNode* newTreeNode()
{
  treeNode* temp = (treeNode*) malloc (sizeof(treeNode));
  temp->children = startList();
  if(temp == NULL)
  {
    printf("Problema de alocacao.");
    exit(1);
  }
  else
    return temp;
}