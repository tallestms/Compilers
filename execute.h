#ifndef EXECUTE_H_
#define EXECUTE_H_

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "hash.h"
#include "variables.h"
#include "stack.h" 
#include "program.h"

void *executeFunction(treeNode *func);
void executeTree(Program* p);
void* executeNode(treeNode* t);

#endif /*EXECUTE_H_*/
