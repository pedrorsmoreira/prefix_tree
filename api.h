/* Prevent multiple inclusions                                      */
#ifndef API
#define API

#include "node.h"
#include "fifo.h"
#include "utils.h"

Node* PrefixTree (char* filename);

Node* InsertPrefix (Node* root, char prefix[], int nextHop);

void PrintTable (Node* root);

int LookUp (Node* root, char addr[]);

Node* DeletePrefix (Node* root, char* prefix);

Node* CompressTree (Node* root);

/* End if: Protect multiple inclusions                              */
#endif