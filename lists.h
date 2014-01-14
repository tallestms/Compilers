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
List* insertBeginList(List* list, void* info);
void* removeBeginList(List** list);
List* seekList(List *list, void *info, int (*compare)(void*, void*));
List* bubbleSortList(List *list, int (*compare)(void*, void*));
List* reverseList(List* l);
void destroyList(List* l);

#endif /* LIST_H_ */