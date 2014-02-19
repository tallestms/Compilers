#ifndef STACK_H_
#define STACK_H_
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stackNode{
	List *first;
};
typedef struct stackNode Stack;

Stack *createStack(void);
void* popStack(Stack *p);
void pushStack(Stack* p, void * v);
int emptyStack (Stack* p);
void freeStack (Stack* p);

#endif /* STACK_H_ */






