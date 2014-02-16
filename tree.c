#include "lists.h"
#include "tree.h"

treeNode* newTreeNode()
{
  treeNode* temp = (treeNode*) malloc (sizeof(treeNode));
  temp->type = -1;
  temp->children1 = NULL;
  temp->children2 = NULL;
  temp->children3 = NULL;
  temp->children4 = NULL;
  temp->next = NULL;
  return temp;
}

int hasNext(treeNode* t){
	return (t->next != NULL);
}


