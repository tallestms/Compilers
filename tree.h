#ifndef TREE_H_
#define TREE_H_
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNodeStruct {
  int type;
  void* children1;
  void* children2;
  void* children3;
  void* children4;
  struct treeNodeStruct *next;
};
typedef struct treeNodeStruct treeNode;

treeNode* newTreeNode();

int hasNext(treeNode* t);

#endif /* TREE_H_ */
