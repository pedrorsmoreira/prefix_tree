/* Prevent multiple inclusions                                      */
#ifndef NODE
#define NODE

// Structures
struct node  
{ 
		size_t nextHop;
		struct node *left; 
		struct node *right;
		struct intList * hopsList;
};

struct node * newNode (size_t nextHop);

/* End if: Protect multiple inclusions                              */
#endif