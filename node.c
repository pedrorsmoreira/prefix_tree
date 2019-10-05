struct node  
{ 
		int prefix;
		int nextHop;
		struct node *left; 
		struct node *right; 
}; 
	
/* newNode() allocates a new node with the given data and NULL left and  
	 right pointers. */
struct node* newNode(int data, int nextHop) 
{ 
	// Allocate memory for new node  
	struct node* node = (struct node*)malloc(sizeof(struct node)); 
	
	// Assign data to this node 
	node->data = data; 
	node->nextHop = nextHop;

	// Initialize left and right children as NULL 
	node->left = NULL; 
	node->right = NULL; 
	return(node); 
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

void print_tree (struct node * root){
	if (root == NULL){
		print("empty tree\n");
		return;
	}

	print ("||  %d  ||  %d  ||\n", prefix, next_hop);

	if (root -> left != NULL)
		print_tree (root -> left);
	if (root -> right != NULL)
		print_tree(root -> right);

	return;
}

