/* Prevent multiple inclusions                                      */
#ifndef NODE
#define NODE

struct node  
{ 
		size_t nextHop;
		struct node* left; 
		struct node* right;
		struct intList* hopsList;
};

typedef struct node Node;

Node* newNode (size_t nextHop);

/* End if: Protect multiple inclusions                              */
#endif