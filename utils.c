#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, Node** nodeToStartDeleting, Node* pointer)
{
	*auxToStartDeleting = value;
	*nodeToStartDeleting = pointer;
}

int getDigits(int h) {
	int size = 0;
	while(h!=0) {
		h = h/10;
		size++;
	}
}

void print(char p[16], int h){
	printf("|| ");
	for (int i = 0;  i < (int) floor( (16 - strlen(p) )/ (double) 2); i++){
		printf(" ");
	}
	printf("%s", p);
	for (int i = 0;  i < (int) ceil( (16 - strlen(p) )/ (double) 2); i++){
		printf(" ");
	}
	printf(" || ");

	int size = getDigits(h);
	for (int i = 0;  i < (int) floor((8 - size )/ (double) 2); i++){
		printf(" ");
	}
	printf("%d", h);
	for (int i = 0;  i < (int) ceil((8 - size )/ (double) 2) ; i++){
		printf(" ");
	}
	printf(" ||\n");
}

Node* PassOneTwo (Node* root)
{
	//step 1
	if (root->left == NULL) {
		if (root->right == NULL) { //leaf
			root->hopsList = newIntList(root->nextHop);
			return root;
		}
		else { //1 right child
			root->left = newNode(root->nextHop);
			if (root->right->nextHop == 0)
				root->right->nextHop = root->nextHop;
		}
	}
	else if (root->right == NULL) { //1 left child
		root->right = newNode(root->nextHop);
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
	}
	else { //2 childs
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
		if (root->right->nextHop == 0)
			root->right->nextHop = root->nextHop;
	}

	root->nextHop = 0;

	struct intList * hopsList1 = PassOneTwo(root->left)->hopsList;
	struct intList * hopsList2 = PassOneTwo(root->right)->hopsList;

	//step2
	root->hopsList = intersect_union (hopsList1, hopsList2);

	return root;
}

bool search (IntList* hopsList, int value)
{
	// Case of receiving 0 from the parent
	if (value == 0)
		return 0;

    while (hopsList != NULL) 
    {
        if (hopsList->hop == value) 
            return 1; 
        hopsList = hopsList->next; 
    }

    return 0; 
}

Node* PassThree (Node* aux, int nextHop)
{
	int value = 0;

	if (search (aux->hopsList, nextHop)) {
		value = nextHop;
		aux->nextHop = 0;
	}
	else {
		aux->nextHop = aux->hopsList->hop;
		value = aux->nextHop;
	}

	emptyIntList(aux->hopsList);

	if (aux->left == NULL) {
		if (aux->right == NULL) {
			if (aux->nextHop == 0) {
				free(aux);
				return NULL;
			}
		}
		else
			aux->right = PassThree (aux->right, value);
	}
	else {
		aux->left = PassThree (aux->left, value);
		if (aux->right != NULL)
			aux->right = PassThree (aux->right, value);
	}

	return aux;
}