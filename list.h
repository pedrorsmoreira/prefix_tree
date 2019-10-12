/* Prevent multiple inclusions                                      */
#ifndef LIST
#define LIST

#include "node.h"

typedef struct intList IntList;

IntList* newIntList (size_t value);

void emptyIntList(IntList* list);

IntList* intersect(IntList* list1, IntList* list2);

/* End if: Protect multiple inclusions                              */
#endif