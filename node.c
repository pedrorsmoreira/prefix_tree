
struct node  
{ 
		size_t nextHop;
		struct node *left; 
		struct node *right; 
}; 
	
/* newNode() allocates a new node with the given prefix and NULL left and  
	 right pointers. */
struct node* newNode(size_t nextHop) 
{ 
	// Allocate memory for new node  
	struct node* node = (struct node*)malloc(sizeof(struct node)); 
	
	// Assign prefix to this node  
	node->nextHop = nextHop;

	// Initialize left and right children as NULL 
	node->left = NULL; 
	node->right = NULL; 
	return(node); 
}

void InsertPrefix(struct node * root, char [] prefix, size_t nextHop){
	if (root == NULL){
		root = newNode(nextHop);
		return;
	}

	for (int i = 0; i = strlen(prefix); i++){
		if (prefix[i] == 0){
			if (root->left == NULL){
				root->left = newNode(0);
				return;
			}
			root = root->left;
		}
		else{
			if (root->right == NULL){
				root->right = newNode(0);
				return;
			}
			root = root->right;
		}
	}
	root->nextHop = nextHop;
	return;
}

size_t LookUp (struct node * root, char [] addr){
	if (root == NULL){
		print("empty tree\n");
		return;
	}

	size_t nextHop;
	for (int i = 0; i < strlen(addr) && root != NULL; i++)
		if (root->nextHop > 0)
			nextHop = root->nextHop;
		if (addr[i] == '0')
			root = root->left;
		else
			root = root->right;
	}
	return nextHop;
}

void PrintTable (struct node * root){
	if (root == NULL) printf("empty tree\n");

	struct fifoTips tips;
	put (tips, "0", root);
	while (!isEmpty(tips)){
		struct fifo * element = get(tips);
		if (element->node->nextHop != 0)
			printf("||  %s  ||  %zu  ||\n", element->prefix, element->node->nextHop);

		int level = strlen(element->prefix) - 1;
		if (element->node->left != NULL){
			element->prefix[level] = 0;
			put (tips, element->prefix, element->node->left);
		}
		if (element->node->right != NULL){
			element->prefix[level] = 1;
			put (tips, element->prefix, element->node->right);
		}
		free (element);
	}
	return;
}




struct fifo{
	char prefix [16];
	struct node * node;
	struct fifo * next;
};

struct fifoTips{
	struct fifo * head;
	struct fifo * tail;
};

bool isEmpty(struct fifoTips tips){
	return (tips.head == NULL)
}

void put(struct fifoTips tips, char [16] prefix, struct node * node){
	struct fifo * element = (struct fifo *)malloc(sizeof(struct fifo));
	element->node = node;
	element->next = NULL;

	if (tips.tail == NULL){
		tips.tail = element;
		tips.head = element;
	}
	else{
		tips.tail->next = element;
		tips.tail = element;
	}
}

struct fifo * get(struct fifoTips tips){
	struct fifo * ret = tips.head;
	tips.head = tips.head->next;
	return ret;
}