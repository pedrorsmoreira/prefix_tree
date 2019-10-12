/* Prevent multiple inclusions                                      */
#ifndef UTILS
#define UTILS

#include "node.h"
#include "list.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, Node** nodeToStartDeleting, Node* pointer);

int getDigits(int h);

void print(char p[16], int h);

bool search (struct intList* hopsList, int value);

Node* PassOneTwo (Node* root);

Node* PassThree (Node* aux, int nextHop);

/* End if: Protect multiple inclusions                              */
#endif