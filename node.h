/* Prevent multiple inclusions                                      */
#ifndef __NODE__
#define __NODE__

#include <stdbool.h>

typedef struct node node;

typedef struct fifo fifo;

typedef struct fifoTips fifoTips;


struct node* newNode (size_t nextHop);

struct node* PrefixTree (char* filename);

struct node* InsertPrefix (struct node* root, char prefix[], size_t nextHop);

size_t LookUp (struct node* root, char addr[]);

bool isEmpty ();

void put (char prefix[16], struct node* node);

struct fifo * get ();

void PrintTable (struct node* root);

struct node* DeletePrefix (struct node* root, char* prefix);


/* End if: Protect multiple inclusions                              */
#endif