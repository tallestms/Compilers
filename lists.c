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
	List *aux;
    List* s = (List*) malloc(sizeof(List));
    if(s == NULL)
    {
        exit(1);
    }
    s->info = info;
    if(list==NULL){
    	s->next = NULL;
      list=s;
    } else {
    	aux = list;
    	while(aux->next) aux = aux->next;
    	aux->next = s;
    }
    
    return list;
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
		free(aux);
		destroyList(l);
	}
}

int sizeList(List *l)
{
	List* aux=l;
	int i=0;
	while(aux!=NULL)
	{
	  aux = aux->next;
	  i++;
	}
	return i;
}

void* getListPosition(List *list, int pos){
	List *aux = list;
	int i;
	for(i=0;aux!=NULL && i<pos;i++){aux=aux->next;}
	if(i<pos){
		return NULL;
	}
	return aux->info;
}
