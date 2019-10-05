
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

/*******************************************************************************/

struct node* PrefixTree(char* filename)
{
	FILE *fp = fopen( filename, "r" );
	if( fp == NULL )
	{
		perror( filename );
		exit(1);
	}

	struct node *root;

	char line[128]; /* maximum line size */

	while( fgets( line, sizeof line, fp ) != NULL ) // read a line
	{
		// Returns first token
		char *token = strtok(line, " ");
		char *token2 = strtok(NULL, " ");

		printf("token: %s\n", token);
		printf("token2: %s\n", token2);

		if( ( token == NULL ) && ( token2 == NULL ) )
		{
			printf("Input file in the wrong structure");
			exit(1);
		}

		if(token[0] == 'e')
			root = InsertPrefix(NULL, token, atoi(token2));
		else
			root = InsertPrefix(root, token, atoi(token2));

		printf("next line\n\n");
	}

	fclose( fp );

	return root;
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

struct node* DeletePrefix(struct node* root, char * prefix)
{
	struct nodeToDelete* deleteList = NULL;
	struct node* aux = root;

	struct node* nodeToStartDelete = NULL;

	if( root == NULL )
	{
		print("Empty tree\n");
		return root;
	}

	// NON SENSE
	if(prefix[0] == 'e')
	{
		if( (root->left == NULL ) && (root->right == NULL) )
			return NULL;

		root->nextHop = 0;

		return root;
	}

	for(int i = 0; i = strlen(prefix); i++)
	{
		if(prefix[i] == '0')
		{
			if(aux->left == NULL)
			{
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if( (aux->left->nextHop == 0) && ( ( aux->left->left == NULL ) || ( aux->left->right == NULL ) ) )
				{
					if(nodeToStartDelete == NULL)
						nodeToStartDelete = aux;
				}

				aux = aux->left;
			}
		}
		else if((prefix[i] == '1'))
		{
			if(aux->right == NULL)
			{
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if( (aux->right->nextHop == 0) && ( ( aux->right->left == NULL ) || ( aux->right->right == NULL ) ) )
				{
					if(previousDelete == NULL)
						previousDelete = aux;
					
					deleteList = insertNewNodeToDelete(deleteList, aux->right);
				}
				else
				{
					ELIMINAR A LISTA
				}

				aux = aux->right;
			}
		}
		else
		{
			printf("Prefix invalid\n");
		}
	}

	deleteList = insertNewNodeToDelete(deleteList, aux);
}



struct nodeToDelete  
{ 
		struct node *pointer;
		struct nodeToDelete *next; 
}; 
	
/* newNode() allocates a new node with the given prefix and NULL left and  
	 right pointers. */
struct nodeToDelete* insertNewNodeToDelete(struct nodeToDelete* head, struct node *pointer) 
{ 
	// Allocate memory for new node  
	struct nodeToDelete* deleteList = (struct nodeToDelete*)malloc(sizeof(struct nodeToDelete)); 
	
	// Assign prefix to this node  
	deleteList->pointer = pointer;

	// Initialize left and right children as NULL 
	deleteList->next = head;

	return(deleteList);

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