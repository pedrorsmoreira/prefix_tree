#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

extern FifoTips tips;

Node* PrefixTree (char* filename)
{
	FILE *fp = fopen (filename, "r");
	if (fp == NULL) {
		perror (filename);
		exit(1);
	}

	Node* root = NULL;

	char line[128]; /* maximum line size */

	// read a line
	while (fgets (line, sizeof line, fp) != NULL) { 
		// Returns first token
		char *token = strtok (line, " ");
		char *token2 = strtok (NULL, " ");

		if ((token == NULL) && (token2 == NULL)) {
			printf("Input file in the wrong structure\n");
			exit(1);
		}

		root = InsertPrefix (root, token, atoi(token2));
	}

	fclose (fp);

	return root;
}

Node* InsertPrefix (Node* root, char prefix[], int nextHop)
{
	int length = strlen(prefix);

	if (root == NULL)
		root = newNode(0);

	if (length == 1 && prefix[0] == 'e' || prefix == ""){
		root->nextHop = nextHop;
		return root;
	}

	Node* aux = root;
	for (int i = 0; i < length; i++) {
		if (prefix[i] == '0') {
			if (aux->left == NULL)
				aux->left = newNode(0);

			aux = aux->left;
		}
		else {
			if (aux->right == NULL)
				aux->right = newNode(0);

			aux = aux->right;
		}
	}

	aux->nextHop = nextHop;
	
	return root;
}

void PrintTable (Node* root)
{
	if (root == NULL) 
		printf("Empty Tree\n");

	tips.head = NULL;
	put ("", root);
	
	do {
		Fifo * element = get();
		if (element->node->nextHop != 0)
			print(element->prefix, element->node->nextHop);

		if (element->node->left != NULL) {
			strcat(element->prefix, "0");
			put (element->prefix, element->node->left);
			if (element->node->right != NULL) {
				element->prefix[strlen(element->prefix)-1] = '1';
				put (element->prefix, element->node->right);
			}
		}
		else if (element->node->right != NULL) {
			strcat(element->prefix, "1");
			put (element->prefix, element->node->right);
		}
		free (element);
	} while (!isEmpty());
	
	return;
}

int LookUp (Node* root, char addr[])
{
	if (root == NULL) {
		printf("Empty Tree\n");
		return 0;
	}
	if (addr == "e")
		addr = "";

	int nextHop = root->nextHop;
	for (int i = 0; i < strlen(addr); i++) {	
		if (addr[i] == '0')
			root = root->left;
		else
			root = root->right;
		
		if (root == NULL)
			break;
		else
			if (root->nextHop > 0)
				nextHop = root->nextHop;
	}

	return nextHop;
}

Node* DeletePrefix (Node* root, char prefix[])
{
	Node* aux = root;

	int auxToStartDeleting = 2;
	Node* nodeToStartDeleting = NULL;

	if (root == NULL) {
		printf("Empty tree\n");
		return root;
	}

	// Elimating default entrance
	if (prefix[0] == 'e') {
		if ((root->left == NULL) && (root->right == NULL))
			return NULL;

		root->nextHop = 0;

		return root;
	}

	for (int i = 0; i < strlen(prefix); i++) {
		if (prefix[i] == '0') {
			if (aux->left == NULL) {
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else {
				if ((aux->left->left != NULL) && (aux->left->right != NULL))
					updateDeletingVariables (&auxToStartDeleting, 2, &nodeToStartDeleting, NULL);
				else if ((aux->left->left != NULL) || (aux->left->right != NULL)) {
					if (aux->left->nextHop == 0) {
						if (nodeToStartDeleting == NULL)
							updateDeletingVariables (&auxToStartDeleting, 0, &nodeToStartDeleting, aux);
					}
					else
						updateDeletingVariables (&auxToStartDeleting, 2, &nodeToStartDeleting, NULL);
				}
				else {
					if (nodeToStartDeleting == NULL)
						updateDeletingVariables (&auxToStartDeleting, 0, &nodeToStartDeleting, aux);
				}

				aux = aux->left;
			}
		}
		else if (prefix[i] == '1') {
			if (aux->right == NULL) {
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else {
				if ((aux->right->left != NULL) && (aux->right->right != NULL))
					updateDeletingVariables (&auxToStartDeleting, 2, &nodeToStartDeleting, NULL);
				else if ((aux->right->left != NULL) || (aux->right->right != NULL)) {
					if (aux->right->nextHop == 0) {
						if (nodeToStartDeleting == NULL)
							updateDeletingVariables (&auxToStartDeleting, 1, &nodeToStartDeleting, aux);
					}
					else
						updateDeletingVariables (&auxToStartDeleting, 2, &nodeToStartDeleting, NULL);
				}
				else {
					if (nodeToStartDeleting == NULL)
						updateDeletingVariables (&auxToStartDeleting, 1, &nodeToStartDeleting, aux);
				}

				aux = aux->right;
			}
		}
		else {
			printf("Prefix invalid\n");
			return root;
		}
	}

	// Deleting part
	if (nodeToStartDeleting == NULL)
		aux->nextHop = 0;
	else {
		if (auxToStartDeleting == 0) {
			aux = nodeToStartDeleting->left;
			nodeToStartDeleting->left = NULL;
		}
		else {
			aux = nodeToStartDeleting->right;
			nodeToStartDeleting->right = NULL;
		}

		while(aux != NULL) {
			if(aux->left != NULL)
				nodeToStartDeleting = aux->left;
			else
				nodeToStartDeleting = aux->right;

			free(aux);
			aux = nodeToStartDeleting;
		}
	}

	return root;
}

Node* CompressTree (Node* root)
{
	// Pass One and Two
	root = PassOneTwo (root);

	// Pass Three
	root->nextHop = root->hopsList->hop;

	emptyIntList(root->hopsList);

	root->left = PassThree (root->left, root->nextHop);
	root->right = PassThree (root->right, root->nextHop);

	return root;
}
