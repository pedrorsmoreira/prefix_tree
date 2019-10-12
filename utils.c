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

void printAll (IntList* head)
{
	printf("Lista de Hops: \n");

    while (head != NULL) {
    	printf("%d\n", head->hop);
    	head = head->next;
    }

    printf("\n");
}

Node* PassOneTwo (Node* root)
{
	//step 1
	if (root->left == NULL) {
		if (root->right == NULL) { //leaf
			printf("FOLHA\n");
			root->hopsList = newIntList(root->nextHop);
			printAll(root->hopsList);
			return root;
		}
		else { //1 right child
			printf("CRIAR NÓ ESQUERDA\n");
			root->left = newNode(root->nextHop);
			if (root->right->nextHop == 0)
				root->right->nextHop = root->nextHop;
		}
	}
	else if (root->right == NULL) { //1 left child
		printf("CRIAR NÓ DIREITA\n");
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
	root->hopsList = intersect(hopsList1, hopsList2);

	printAll(root->hopsList);

	return root;
}

bool search (IntList* hopsList, int value)
{
	// XXXXXXXXXXXXXX
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

	printf("\nVALOR QUE VEM DO PAI %d\n", nextHop);

	printAll(aux->hopsList);

	if (search (aux->hopsList, nextHop)) {
		printf("TÁ NA LISTA VAI SER 0\n");
		value = nextHop;
		aux->nextHop = 0;
	}
	else {
		aux->nextHop = aux->hopsList->hop;
		value = aux->nextHop;
		printf("NÃO TÁ NA LISTA VAI SER %d\n", aux->nextHop);
	}

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
		printf("VIM AQUI!!\n");
		aux->left = PassThree (aux->left, value);
		if (aux->right != NULL)
			aux->right = PassThree (aux->right, value);
	}

	return aux;
}