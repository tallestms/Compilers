#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

List* startList(void)
{
    return NULL;
}

int emptyList(List* list)
{
    return (list == NULL);
}

List* insertList(List* list, void* info)
{
    List* s = (List*) malloc(sizeof(List));
    if(s == NULL)
    {
        exit(1);
    }
    s->info = info;
    s->next = list;
    return s;
}

void* removeList(List** list)
{
    List* aux;
    void* info;
    if(emptyList(*list))
    {
    	   free(aux);
        return NULL;
    }
    else
    {
    	info = (*list)->info;
        aux = *list;
        *list = (*list)->next;
        free(aux);
        return info;
    }
}

List* seekList(List *list, void *info, int (*compare)(void*, void*))
{
	while(list != NULL)
	{
		if(compare(info, list->info))
		{
			return list;
		}
		list = list->next;
	}
	return list;
}

List* bubbleSortList(List *list, int (*compare)(void*, void*))
{
	List *first, *last;
	first = list;
	last = NULL;
	char change;
	if(first == NULL)			/* Verifica o caso: lista vazia - não é necessário ordenação. */
		return first;

	while(first != last)
	{
		change = FALSE;
		while(list->next != last)
		{
			if(compare(list->info, list->next->info))
			{
				void *aux = list->info;
				list->info = list->next->info;
				list->next->info = aux;
				change = TRUE;
			}
			list = list->next;
		}
		last = list;
		list = first;
		if(!change)
			return first;
	}
	return first;
}

List* reverseList(List* list)
{
	List *before = NULL, *after, *auxList;
	if(list != NULL)
	{
		after = list->next;
		while(list->next != NULL && after != NULL)
		{
			list->next = before;
			auxList = after->next;
			after->next = list;
			list = auxList;
			before = after;
			if(list == NULL)
				return before;
			after = list->next;
			list->next = before;
		}
	}
	return list;
}

void destroyList(List *l)
{
	List* aux;
	if(!emptyList(l))
	{
		aux = l;
		l = l->next;
		if(!emptyList(aux->info))
		{
			free(aux->info);
		}
		free(aux);
		destroyList(l);
	}
}