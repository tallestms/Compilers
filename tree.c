#include "lists.h"
#include "tree.h"

treeNode* newTreeNode()
{
  treeNode* temp = (treeNode*) malloc (sizeof(treeNode));
  temp->type[0] = '\0';
  temp->value[0] = '\0';
  temp->children[0] = NULL;
  temp->children[1] = NULL;
  temp->children[2] = NULL;
  temp->children[3] = NULL;
  temp->next = NULL;
  return temp;
}

int hasNext(treeNode* t){
	return (t->next != NULL);
}

void fillTreeNode(treeNode* arv, char value[50], char type[50]){
	strcpy(arv->type, type);
	strcpy(arv->value, value);
}
