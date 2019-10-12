/* Prevent multiple inclusions                                      */
#ifndef UTILS
#define UTILS

#include "node.h"
#include "list.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, Node** nodeToStartDeleting, Node* pointer);

Node* PassOneTwo (Node* root);

bool search (struct intList* hopsList, int value);

Node* PassThree (Node* aux, int nextHop);

/* End if: Protect multiple inclusions                              */
#endif