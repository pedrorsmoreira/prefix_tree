#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"

struct node  
{ 
		size_t nextHop;
		struct node *left; 
		struct node *right; 
}; 

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

	struct node *root = NULL;

	char line[128]; /* maximum line size */

	while (fgets (line, sizeof line, fp) != NULL) // read a line
	{
		// Returns first token
		char *token = strtok (line, " ");
		char *token2 = strtok (NULL, " ");

		printf("token: %s\n", token);
		printf("token2: %s\n", token2);

		if ((token == NULL) && (token2 == NULL))
		{
			printf("Input file in the wrong structure\n");
			exit(1);
		}

		root = InsertPrefix (root, token, atoi(token2));

		printf("next line\n\n");
	}

	fclose (fp);

	return root;
}

struct node* InsertPrefix (struct node * root, char prefix[], size_t nextHop)
{
	if (root == NULL)
	{
		printf("iuuuu criei o nó e\n");
		root = newNode(nextHop);
		return root;
	}

	struct node* aux = root;

	for (int i = 0; i < strlen(prefix); i++)
	{
		if (prefix[i] == '0')
		{
			if (aux->left == NULL)
				aux->left = newNode(0);

			aux = aux->left;
		}
		else
		{
			if (aux->right == NULL)
				aux->right = newNode(0);

			aux = aux->right;
		}
	}

	aux->nextHop = nextHop;
	
	return root;
}

size_t LookUp (struct node * root, char addr[])
{
	if (root == NULL)
	{
		printf("Empty Tree\n");
		return 0;
	}

	size_t nextHop = root->nextHop;
	for (int i = 0; i < strlen(addr); i++)
	{	
		if (addr[i] == '0')
			root = root->left;
		else
			root = root->right;
		
		if (root == NULL)
			break;
		else
			if (root->nextHop > 0)
				nextHop = root->nextHop;
	}

	return nextHop;
}

bool isEmpty (struct fifoTips tips)
{
	return (tips.head == NULL);
}

void put (struct fifoTips tips, char prefix[16], struct node * node)
{
	struct fifo * element = (struct fifo *)malloc(sizeof(struct fifo));
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

struct fifo * get (struct fifoTips tips)
{
	struct fifo * ret = tips.head;
	tips.head = tips.head->next;
	return ret;
}

void PrintTable (struct node * root)
{
	if (root == NULL) 
		printf("Empty Tree\n");

	struct fifoTips tips;
	tips.head = NULL;
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

struct node* DeletePrefix (struct node* root, char prefix[])
{
	struct node* aux = root;

	int auxToStartDeleting = 2;
	struct node* nodeToStartDeleting = NULL;

	if (root == NULL)
	{
		printf("Empty tree\n");
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

	for (int i = 0; i < strlen(prefix); i++)
	{
		if (prefix[i] == '0')
		{
			printf("Left\n");

			if (aux->left == NULL)
			{
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if ((aux->left->left != NULL) && (aux->left->right != NULL))
				{
					auxToStartDeleting = 2;
					nodeToStartDeleting = NULL;
				}
				else if ((aux->left->left != NULL) || (aux->left->right != NULL))
				{
					if (aux->left->nextHop == 0)
					{
						if (nodeToStartDeleting == NULL)
						{
							auxToStartDeleting = 0;
							nodeToStartDeleting = aux;
						}
					}
					else
					{
						auxToStartDeleting = 2;
						nodeToStartDeleting = NULL;
					}
				}
				else
				{
					if (nodeToStartDeleting == NULL)
					{
						auxToStartDeleting = 0;
						nodeToStartDeleting = aux;
					}
				}

				aux = aux->left;
			}
		}
		else if (prefix[i] == '1')
		{
			printf("Right\n");

			if (aux->right == NULL)
			{
				printf("Don't exist that prefix in the tree\n");
				return root;
			}
			else
			{
				if ((aux->right->left != NULL) && (aux->right->right != NULL))
				{
					auxToStartDeleting = 2;
					nodeToStartDeleting = NULL;
				}
				else if ((aux->right->left != NULL) || (aux->right->right != NULL))
				{
					if (aux->right->nextHop == 0)
					{
						if (nodeToStartDeleting == NULL)
						{
							auxToStartDeleting = 1;
							nodeToStartDeleting = aux;
						}
					}
					else
					{
						auxToStartDeleting = 2;
						nodeToStartDeleting = NULL;
					}
				}
				else
				{
					if (nodeToStartDeleting == NULL)
					{
						auxToStartDeleting = 1;
						nodeToStartDeleting = aux;
					}
				}

				aux = aux->right;
			}
		}
		else
		{
			printf("Prefix invalid\n");
		}
	}

	printf("aux->nextHop: %d\n", aux->nextHop);
	printf("nodeToStartDeleting->nextHop: %d\n", nodeToStartDeleting->nextHop);
	printf("nodeToStartDeleting->right->nextHop: %d\n", nodeToStartDeleting->right->nextHop);

	// Deleting part
	if (nodeToStartDeleting == NULL)
		aux->nextHop = 0;
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
				nodeToStartDeleting = aux->left;
			else
				nodeToStartDeleting = aux->right;

			free(aux);
			aux = nodeToStartDeleting;
		}
	}

	return root;
}