#include "stack.h"

Stack *createStack(void)
{
	Stack *s = (Stack*) malloc(sizeof(Stack));
	s -> first = NULL;
	return s;
}

void* popStack(Stack *p)
{
	List* t;
	void* v;
	if (emptyStack(p)) {
		printf("Pilha vazia.\n");
		exit(1);
	}
	t = p -> first;
	v = t -> info;
	p -> first = t -> next;
	free(t);
	return v;
}

void pushStack(Stack* p, void * v)
{
	List* n = (List*)malloc(sizeof(List));
	n->info = v;
	n->next = p->first;
	p->first = n;
}
int emptyStack (Stack* p)
{
	return (p->first == NULL);
}

void freeStack (Stack* p)
{
	List* q = p -> first;
	while (q!=NULL) {
		List *t = q -> next;
		free(q);
		q = t;
	}
	free(p);
}


