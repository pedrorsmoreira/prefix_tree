#include <stdio.h>
#include <stdlib.h>

#include "list.h"


IntList* newIntList (size_t value) 
{ 
	// Allocate memory for new node  
	IntList* list = (IntList*) malloc (sizeof(IntList)); 
	list->hop = value;
	list->next = NULL;

	return(list); 
}

void emptyIntList(IntList* list)
{
	IntList* aux = list;

	while (list != NULL) {
		aux = list;
		list = list->next;
		free(aux);
	}
}

IntList* unite(IntList* l1, IntList* l2)
{
	if (l1 == NULL)
		return NULL;

	IntList * l = newIntList(l1->hop);
	IntList * head = l;

	l1 = l1->next;
	while(l1 != NULL){
		l->next = newIntList(l1->hop);
		l = l->next;
		l1 = l1->next;
	}
	while(l2 != NULL){
		l->next = newIntList(l2->hop);
		l = l->next;
		l2 = l2->next;
	}
	return head;
}

IntList* intersect(IntList* list1, IntList* list2)
{
	IntList* aux1 = list1, *aux2, *result = NULL, *result_aux;

	while (1) {
		aux2 = list2;
		while (aux2 != NULL) {
			if(aux1->hop == aux2->hop) {
				if (result == NULL) {
					result = newIntList(aux1->hop);
					result_aux = result;
				}
				else {
					result_aux->next = newIntList(aux1->hop);
					result_aux = result_aux->next;
				}
			}
			aux2 = aux2->next;
		}
		if (aux1->next == NULL) break;
		else aux1 = aux1->next;
	}

	if (result == NULL)
		result = unite(list1, list2);

	return result;
}