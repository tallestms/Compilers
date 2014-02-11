#ifndef TREE_H_
#define TREE_H_
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNodeStruct {
  void* element;
  List* children;
  struct treeNodeStruct *next;
};
typedef struct treeNodeStruct treeNode;

treeNode* newTreeNode();



#endif /* TREE_H_ */