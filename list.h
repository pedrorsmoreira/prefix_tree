/* Prevent multiple inclusions                                      */
#ifndef LIST
#define LIST

#include "node.h"

struct intList 
{
	int hop;
	struct intList * next;
};

typedef struct intList IntList;

IntList* newIntList (size_t value);

void emptyIntList(IntList* list);

IntList* unite(IntList* l1, IntList* l2);

IntList* intersect_union(IntList* list1, IntList* list2);

/* End if: Protect multiple inclusions                              */
#endif