/* Prevent multiple inclusions                                      */
#ifndef UTILS
#define UTILS

#include "node.h"
#include "list.h"

void updateDeletingVariables (int* auxToStartDeleting, int value, Node** nodeToStartDeleting, struct node* pointer);

int getDigits(int h);

void print(char p[16+1], int h);

struct node* PassOneTwo (Node* root);

bool search (IntList* hopsList, int value);

struct node* PassThree (Node* aux, int nextHop);

/* End if: Protect multiple inclusions                              */
#endif