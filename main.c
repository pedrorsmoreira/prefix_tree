#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "node.h"

void print_usage(char*);

int main(int argc, char *argv[]) 
{ 
	int opt;
	char* filename = NULL;

	while ((opt = getopt(argc, argv, "f:")) != -1) 
	{
		switch (opt) 
		{
			case 'f':
				filename = optarg;
				break;

			default:
				print_usage(argv[0]);
				exit(1);
		}
	}

	struct node* root = PrefixTree (filename);
	PrintTable(root);

/*
	printf("Prefix %s Next-hop: %d\n", "11010011", LookUp (root, "11010011"));
	printf("Prefix %s Next-hop: %d\n", "11000011", LookUp (root, "11000011"));
	printf("Prefix %s Next-hop: %d\n", "000", LookUp (root, "000"));

	printf("Prefix %s Next-hop: %d\n", "010", LookUp (root, "0"));

	printf("\n");
	//root = DeletePrefix (root, "0");
	printf("\n");

	printf("Prefix %s Next-hop: %d\n", "010",LookUp (root, "0"));*/

	return 0;  
}

void print_usage(char *program)
{
	fprintf(stderr, "Usage: %s [-f input-file]\n", program);
	exit(1);
}