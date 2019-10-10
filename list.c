struct intList 
{
	int hop;
	struct intList * next;
}

struct node* newIntList (size_t value) 
{ 
	// Allocate memory for new node  
	struct intList* list = (struct intList*) malloc (sizeof(struct intList)); 
	list->hop = value;
	list->next = NULL;

	return(list); 
}

void emptyIntList(struct intList * list)
{
	while (list != NULL)
	{
		struct intList * aux = NULL;
		list = list->next;
		free(aux);
	}
};

struct intList * intersect(intList * list1, intList, * list2)
{
	struct intList *aux1=list1, *aux2, *result=NULL, result_aux;

	while (1){
		aux2 = list2;
		while (aux2 != NULL){
			if(aux1->hop == aux2->hop){
				if (result == NULL){
					result = newIntList(aux1->hop);
					result_aux = result;
				}
				else{
					result_aux->next = newIntList(aux1->hop);
					result_aux = result_aux->next;
				}
			}
			aux2 = aux2->next;
		}
		if (aux1->next == NULL) break;
		else aux1 = aux1->next;
	}

	if (result == NULL){
		result = list1;
		aux1->next = list2;
	}

	return result;
}