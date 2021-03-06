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

void printNode(treeNode* t, int type, int nivel, int isNext){
	
	/* TYPE:
		1 - type
		2 - value
		3 - type + value
		11 - type + recursão;
		12 - value + recursão;
		13 - type + value + recursão 
	*/
	if (t==NULL) return;
	
	int temp = type % 10;
	int j;
	for(j=0;j<nivel;j++) {
		if(j%6==0) printf("|"); else printf(" ");
	}
	
	if(isNext){ printf("->");}
	switch(temp){
	case 1: printf("type: %s\n", t->type); break;
	case 2: printf("value: %s\n", t->value); break;
	case 3: printf("type: %s & value: %s \n", t->type, t->value);
		break;
	default: break;
	}
	if(type > 9){
		int i;
		for (i=0;t->children[i]!=NULL;i++){
			printNode(t->children[i], type, nivel+6,0);
		}
		printNode(t->next, type, nivel,1);
	}

}

void copyTreeNodes(treeNode* a, treeNode* b)
{
  strcpy(a->type, b->type);
  strcpy(a->value, b->value);
  a->children[0] = b->children[0];
  a->children[1] = b->children[1];
  a->children[2] = b->children[2];
  a->children[3] = b->children[3];
  a->next = b->next;
}

void desallocNodes(treeNode* t)
{
  /*
	if (t==NULL) return;
	int i;
		for (i=0;i<4;i++)
		{
			desallocNodes(t->children[i]);
		}
		desallocNodes(t->next);
	
	free(t);
	t=NULL; */
}
