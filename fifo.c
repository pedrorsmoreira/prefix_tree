struct fifo
{
	char prefix [16];
	struct node * node;
	struct fifo * next;
};

struct fifoTips
{
	struct fifo * head;
	struct fifo * tail;
};


struct fifoTips tips;


bool isEmpty ()
{
	return (tips.head == NULL);
}

void put (char prefix[16], struct node * node)
{
	struct fifo * element = (struct fifo *)malloc(sizeof(struct fifo));
	strcpy(element->prefix, prefix);
	element->node = node;
	element->next = NULL;

	if (tips.head == NULL){
		tips.tail = element;
		tips.head = element;
	}
	else{
		tips.tail->next = element;
		tips.tail = element;
	}
}

struct fifo * get ()
{
	struct fifo * ret = tips.head;
	tips.head = tips.head->next;
	return ret;
}