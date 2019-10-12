/* Prevent multiple inclusions                                      */
#ifndef FIFO
#define FIFO

#include <stdbool.h>

#include "node.h"

struct fifo
{
	char prefix [16];
	Node* node;
	struct fifo* next;
};

struct fifoTips
{
	struct fifo * head;
	struct fifo * tail;
};

typedef struct fifo Fifo;

typedef struct fifoTips FifoTips;

bool isEmpty ();

void put (char prefix[16], Node* node);

Fifo * get ();

/* End if: Protect multiple inclusions                              */
#endif
