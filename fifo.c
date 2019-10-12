#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fifo.h"

FifoTips tips;

bool isEmpty ()
{
	return (tips.head == NULL);
}

void put (char prefix[16], Node* node)
{
	Fifo * element = (struct fifo *)malloc(sizeof(struct fifo));
	strcpy(element->prefix, prefix);
	element->node = node;
	element->next = NULL;

	if (tips.head == NULL) {
		tips.tail = element;
		tips.head = element;
	}
	else {
		tips.tail->next = element;
		tips.tail = element;
	}
}

Fifo * get ()
{
	Fifo * ret = tips.head;
	tips.head = tips.head->next;
	return ret;
}