
struct node  
{ 
		size_t nextHop;
		struct node *left; 
		struct node *right; 
}; 
	
/* newNode() allocates a new node with the given prefix and NULL left and  
	 right pointers. */
struct node* newNode (size_t nextHop) 
{ 
	// Allocate memory for new node  
	struct node* node = (struct node*) malloc (sizeof(struct node)); 
	
	// Assign prefix to this node  
	node->nextHop = nextHop;

	// Initialize left and right children as NULL 
	node->left = NULL; 
	node->right = NULL; 
	return(node); 
}

/*******************************************************************************/

struct node* PrefixTree (char* filename)
{
	FILE *fp = fopen (filename, "r");
	if (fp == NULL)
	{
		perror (filename);
		exit(1);
	}

	struct node *root;

	char line[128]; /* maximum line size */

	while (fgets (line, sizeof line, fp) != NULL) // read a line
	{
		// Returns first token
		char *token = strtok (line, " ");
		char *token2 = strtok (NULL, " ");

		printf ("token: %s\n", token);
		printf ("token2: %s\n", token2);

		if ((token == NULL) && (token2 == NULL))
		{
			printf ("Input file in the wrong structure");
			exit(1);
		}

		if (token[0] == 'e')
			root = InsertPrefix (NULL, token, atoi(token2));
		else
			root = InsertPrefix (root, token, atoi(token2));

		printf ("next line\n\n");
	}

	fclose (fp);

	return root;
}

void InsertPrefix (struct node * root, char [] prefix, size_t nextHop)
{
	if (root == NULL)
	{
		root = newNode(nextHop);
		return;
	}

	for (int i = 0; i = strlen(prefix); i++)
	{
		if (prefix[i] == 0)
		{
			if (root->left == NULL)
			{
				root->left = newNode(0);
				return;
			}
			root = root->left;
		}
		else
		{
			if (root->right == NULL)
			{
				root->right = newNode(0);
				return;
			}
			root = root->right;
		}
	}
	root->nextHop = nextHop;
	return;
}

size_t LookUp (struct node * root, char [] addr)
{
	if (root == NULL)
	{
		print("empty tree\n");
		return;
	}

	size_t nextHop;
	for (int i = 0; i < strlen(addr) && root != NULL; i++)
	{
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
	while (!isEmpty(tips))
	{
		struct fifo * element = get(tips);
		if (element->node->nextHop != 0)
			printf("||  %s  ||  %zu  ||\n", element->prefix, element->node->nextHop);

		int level = strlen(element->prefix) - 1;
		if (element->node->left != NULL)
		{
			element->prefix[level] = 0;
			put (tips, element->prefix, element->node->left);
		}
		if (element->node->right != NULL)
		{
			element->prefix[level] = 1;
			put (tips, element->prefix, element->node->right);
		}
		free (element);
	}
	return;
}

struct node* DeletePrefix (struct node* root, char * prefix)
{
	struct node* aux = root;

	int intPrev = 2;
	struct node* auxPrev = NULL;

	int auxToStartDeleting = 2;
	struct node* nodeToStartDeleting = NULL;

	if (root == NULL)
	{
		print ("Empty tree\n");
		return root;
	}

	// NON SENSE
	if (prefix[0] == 'e')
	{
		if ((root->left == NULL) && (root->right == NULL))
			return NULL;

		root->nextHop = 0;

		return root;
	}

	for (int i = 0; i = strlen(prefix); i++)
	{
		if (prefix[i] == '0')
		{
			if (aux->left == NULL)
			{
				printf ("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if ((aux->left->nextHop == 0) && ((aux->left->left == NULL) || (aux->left->right == NULL)))
				{
					if (nodeToStartDeleting == NULL)
					{
						nodeToStartDeleting = aux;
						auxToStartDeleting = 0;
					}
				}
				else
				{
					if ((aux->left->left != NULL) || (aux->left->right != NULL))
					{
						nodeToStartDeleting = NULL;
						auxToStartDeleting = 2;
					}
				}

				auxPrev = aux;
				intPrev = 0;
				aux = aux->left;
			}
		}
		else if (prefix[i] == '1')
		{
			if (aux->right == NULL)
			{
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if ((aux->right->nextHop == 0) && ((aux->right->left == NULL) || (aux->right->right == NULL)))
				{
					if (nodeToStartDeleting == NULL)
					{
						nodeToStartDeleting = aux;
						auxToStartDeleting = 1;
					}
				}
				else
				{
					if ((aux->right->left != NULL) || (aux->right->right != NULL))
					{
						nodeToStartDeleting = NULL;
						auxToStartDeleting = 2;
					}
				}

				auxPrev = aux;
				intPrev = 1;
				aux = aux->right;
			}
		}
		else
		{
			printf ("Prefix invalid\n");
		}
	}

	// Deleting part
	if ((aux->left != NULL) || (aux->right != NULL))
		aux->nextHop = 0;
	else
	{
		if (nodeToStartDeleting == NULL)
		{
			if (intPrev == 0)
				auxPrev->left = NULL;
			else
				auxPrev->right = NULL;
			
			free (aux);
		}
		else
		{
			if (auxToStartDeleting == 0)
			{
				aux = nodeToStartDeleting->left;
				nodeToStartDeleting->left = NULL;
			}
			else
			{
				aux = nodeToStartDeleting->right;
				nodeToStartDeleting->right = NULL;
			}

			while(aux != NULL)
			{
				if(aux->left != NULL)
					auxPrev = aux->left;
				else
					auxPrev = aux->right;
				
				free(aux);
				aux = auxPrev;
			}
		}
	}

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