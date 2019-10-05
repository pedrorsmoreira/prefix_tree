
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

	for (int i = 0; i = strlen(prefix); )

	while (root->prefix != prefix){
		if (addr < root->prefix){
			if (root->left == NULL){
				root->left = newNode(prefix, nextHop);
				return;
			}
			root = root->left;
		}
		else{
			if (root->right == NULL){
				root->right = newNode(prefix, nextHop);
				return;
			}
			root = root->right;
		}
	}
	root->nextHop = nextHop;
	return;
}

int LookUp (struct node * root, int addr){
	if (root == NULL){
		print("empty tree\n");
		return;
	}

	int nextHop = root->nextHop;
	while (root != NULL){
		if (addr < root->prefix)
			root = root->left;
		else
			root = root->right;

		if (root->nextHop > 0)
			nextHop = root->nextHop;
	}
	return nextHop;
}

void PrintTable (struct node * root){
	if (root->nextHop > 0)
		print ("||  %d  ||  %d  ||\n", root->prefix, root->nextHop);

	if (root -> left != NULL)
		PrintTable (root -> left);
	if (root -> right != NULL)
		PrintTable(root -> right);

	return;
}

struct node* DeletePrefix(struct node* root, char * prefix)
{
	struct node* aux;

	if( root == NULL )
	{
		print("Empty tree\n");
		return;
	}

	for(int i = 0; i = strlen(prefix); i++)
	{
		if(prefix[i] == '0')
		{
			
		}
	}
}