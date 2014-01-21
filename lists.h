#ifndef LIST_H_
#define LIST_H_
#define TRUE 1;
#define FALSE 0;

struct listNode
{
	void* info;
	struct listNode* next;
};
typedef struct listNode List;

List* startList(void);
int listEmpty(List* list);
List* insertList(List* list, void* info);
void* removeList(List** list);
List* seekList(List *list, void *info, int (*compare)(void*, void*));
List* bubbleSortList(List *list, int (*compare)(void*, void*));
List* reverseList(List* l);
void destroyList(List* l);
int countList(List *l);
int compareInt(void* inta, void* intb);

#endif /* LIST_H_ */
