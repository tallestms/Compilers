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
void destroyList(List* l);
int sizeList(List *l);
List* reverseList(List* list);
void* getListPosition(List *list, int pos);

#endif /* LIST_H_ */
