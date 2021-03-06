#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "hash.h"
#include "tree.h"

struct program
{
	char name[50];
	treeNode *exec;
	hashTable *hashVariables;
	hashTable *hashFunctions;
};
typedef struct program Program;

Program* createProgram();

#endif /*PROGRAM_H_*/
