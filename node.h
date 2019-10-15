/* Prevent multiple inclusions                                      */
#ifndef NODE
#define NODE

struct node  
{ 
		int nextHop;
		struct node* left; 
		struct node* right;
		struct intList* hopsList;
};

typedef struct node Node;

Node* newNode (int nextHop);

/* End if: Protect multiple inclusions                              */
#endif