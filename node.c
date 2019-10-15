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