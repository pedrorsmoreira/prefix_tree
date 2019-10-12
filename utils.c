#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, Node** nodeToStartDeleting, Node* pointer)
{
	*auxToStartDeleting = value;
	*nodeToStartDeleting = pointer;
}

Node* PassOneTwo (Node* root)
{
	//step 1
	if (root->left == NULL){
		if (root->right == NULL){ //leaf
			root->hopsList = newIntList(root->nextHop);
			return root;
		}
		else{ //1 right child
			root->left = newNode(root->nextHop);
			if (root->right->nextHop == 0)
				root->right->nextHop = root->nextHop;
		}
	}
	else if (root->right == NULL){ //1 left child
		root->right = newNode(root->nextHop);
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
	}
	else
	{ //2 childs
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
		if (root->right->nextHop == 0)
			root->right->nextHop = root->nextHop;
	}

	root->nextHop = 0;

	struct intList * hopsList1 = PassOneTwo(root->left)->hopsList;
	struct intList * hopsList2 = PassOneTwo(root->right)->hopsList;

	//step2
	root->hopsList = intersect(hopsList1, hopsList2);

	return root;
}

bool search (struct intList* hopsList, int value)
{
	// XXXXXXXXXXXXXX
	if (value == 0)
		return 0;
	
    struct intList* current = hopsList;  // Initialize current 
    while (current != NULL) 
    { 
        if (current->hop == value) 
            return 1; 
        current = current->next; 
    }

    return 0; 
}

Node* PassThree (Node* aux, int nextHop)
{
	int value = 0;

	if (search (aux->hopsList, nextHop))
	{
		value = nextHop;
		aux->nextHop = 0;
	}
	else
	{
		aux->nextHop = aux->hopsList->nextHop;
		value = aux->nextHop;
	}

	if (aux->left != NULL)
		aux->left = PassThree (aux->left, value);
	if (aux->right != NULL)
		aux->right = PassThree (aux->right, value);

	if (aux->nextHop == 0)
	{
		free(aux);
		return NULL;
	}
	else
		return aux;
}