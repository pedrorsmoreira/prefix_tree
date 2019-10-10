void updateDeletingVariables (int* auxToStartDeleting, int value, struct node** nodeToStartDeleting, struct node* pointer)
{
	*auxToStartDeleting = value;
	*nodeToStartDeleting = pointer;
}

bool search (struct intList* hopsList, int value)
{
    struct intList* current = hopsList;  // Initialize current 
    while (current != NULL) 
    { 
        if (current->hop == value) 
            return true; 
        current = current->next; 
    }

    return false; 
}

struct node* PassThree (struct node* aux, int nextHop)
{
	if (search (aux->hopsList, nextHop))
		aux->nextHop = 0;
	else
		aux->nextHop = aux->hopsList->nextHop;

	if (aux->left != NULL)
		aux->left = PassThree (aux->left, aux->nextHop);
	if (aux->right != NULL)
		aux->right = PassThree (aux->right, aux->nextHop);

	return aux;
}

struct node* PassOneTwo (struct node* root)
{
	//step 1
	if (root->left == NULL){
		if (root->right == NULL){ //leaf
			root->hopsList = newIntList(root->nextHop);
			return root;
		}
		else{ //1 right child
			root->left = newNode(root->nextHop);
			if (root->right->nextHop == 0)
				root->right->nextHop = root->nextHop;
		}
	}
	else if (root->right == NULL){ //1 left child
		root->right = newNode(root->nextHop);
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
	}
	else
	{ //2 childs
		if (root->left->nextHop == 0)
			root->left->nextHop = root->nextHop;
		if (root->right->nextHop == 0)
			root->right->nextHop = root->nextHop;
	}

	root->nextHop = 0;

	struct intList * hopsList1 = PassOneTwo(root->left)->hopsList;
	struct intList * hopsList2 = PassOneTwo(root->right)->hopsList;

	//step2
	root->hopsList = intersect(hopsList1, hopsList2);

	return root;
}