/* Prevent multiple inclusions                                      */
#ifndef UTILS
#define UTILS

#include "node.h"
#include "list.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, struct node** nodeToStartDeleting, struct node* pointer);

struct node* PassOneTwo (struct node* root);

bool search (struct intList* hopsList, int value);

struct node* PassThree (struct node* aux, int nextHop);

/* End if: Protect multiple inclusions                              */
#endif