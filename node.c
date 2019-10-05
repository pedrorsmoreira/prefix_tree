
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

	size_t nextHop = root->nextHop;
	for (int i = 0; i < strlen(addr) && root != NULL; i++)
		if (addr[i] == 0)
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

