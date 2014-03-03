#ifndef TREE_H_
#define TREE_H_
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNodeStruct {
  char type[50];
  char value[50];
  struct treeNodeStruct* children[4];
  struct treeNodeStruct* next;
};
typedef struct treeNodeStruct treeNode;

treeNode* newTreeNode();

int hasNext(treeNode* t);

void fillTreeNode(treeNode *arv, char value[50], char type[50]);

void printNode(treeNode* t, int type, int nivel);

void copyTreeNodes(treeNode* a, treeNode* b);

#endif /* TREE_H_ */
