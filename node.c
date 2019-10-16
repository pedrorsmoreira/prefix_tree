#include <stdlib.h>
#include <stdio.h>

#include "node.h"
	
/* newNode() allocates a new node with the given prefix and NULL left and  
	 right pointers. */
Node* newNode (int nextHop) 
{ 
	// Allocate memory for new node  
	Node* node = (Node*) malloc (sizeof(Node)); 
	
	// Assign prefix to this node  
	node->nextHop = nextHop;

	// Initialize left and right children as NULL 
	node->left = NULL; 
	node->right = NULL;

	node->hopsList = NULL;

	return(node); 
}

void clean(Node * root){
	if (root == NULL) return;
	if (root->left != NULL) clean (root->left);
	if (root->right != NULL) clean (root->right);
	free(root);
}

Node* clone(Node * root, Node * newRoot){
	if (root == NULL)
		return NULL;

	newRoot = newNode(root->nextHop);
	newRoot->left = clone(root->left, newRoot->left);
	newRoot->right = clone(root->right, newRoot->right);
	return newRoot;
}