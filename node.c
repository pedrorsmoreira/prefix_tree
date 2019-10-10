#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"

// Structures

struct node  
{ 
		size_t nextHop;
		struct node *left; 
		struct node *right;
		struct intList * hopsList:
};

extern struct fifo Tips tips;

// Functions
	
/* newNode() allocates a new node with the given prefix and NULL left and  
	 right pointers. */
struct node* newNode (size_t nextHop) 
{ 
	// Allocate memory for new node  
	struct node* node = (struct node*) malloc (sizeof(struct node)); 
	
	// Assign prefix to this node  
	node->nextHop = nextHop;

	// Initialize left and right children as NULL 
	node->left = NULL; 
	node->right = NULL;

	node->hopsList = NULL;

	return(node); 
}