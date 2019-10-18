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

void clean(Node * root);

Node* clone(Node * root, Node * newRoot);

/* End if: Protect multiple inclusions                              */
#endif