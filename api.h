/* Prevent multiple inclusions                                      */
#ifndef API
#define API

#include "node.h"
#include "fifo.h"
#include "utils.h"

Node* PrefixTree (char* filename);

Node* InsertPrefix (Node* root, char prefix[], size_t nextHop);

size_t LookUp (Node* root, char addr[]);

void PrintTable (Node* root);

Node* DeletePrefix (Node* root, char* prefix);

/* End if: Protect multiple inclusions                              */
#endif