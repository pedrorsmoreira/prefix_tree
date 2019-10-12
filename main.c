#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "api.h"

void print_usage(char*);

int main(int argc, char *argv[]) 
{ 
	int opt;
	char* filename = NULL;

	if (argc < 2)
	{
		print_usage(argv[0]);
		exit(1);
	}

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

	//PRIMEIRA TABELA
	Node* root = PrefixTree (filename);
	PrintTable(root);

	while(1){
		//read the action from stdin and perform it
		while (1){
		char order, aux[50], prefix[16], nexthop[16];
			printf("(Enter [Q] to quit) \nIntroduce the action, Print [P], Search [S], Insert [I], Delete [D] or Compress [C]:");
			if (fgets(aux, sizeof(aux), stdin) == NULL){
				perror("fgets: ");
				exit(-1);
			}
			sscanf(aux, "%c", &order);
			//perform
			if ((order == 'q') || (order == 'Q'))
				return 0;

			else if ((order == 'i') || (order == 'I')){
				printf("Write the prefix to be inserted:");	
				if (fgets(prefix, 16, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				printf("Write the nexthop:");	
				if (fgets(nexthop, 16, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				Node* r = InsertPrefix(root, prefix, atoi(nexthop));
				if (r != NULL) root = r;
				else printf("invalid input.\n---\n\n");

				break;
			}
			else if ((order == 'P') || (order == 'p')){
				PrintTable(root);
				break;
			}
			else if ((order == 'W') || (order == 'w')){
				//read the region of the action from stdin
				region = read_region();
				
				nbytes = clipboard_wait(fd, region, message, MESSAGE_SIZE);
				if (nbytes == 0)	printf("paste (wait) failed\n---\n");
				else	printf("Received %s\n (%d bytes pasted (wait))\n---\n", message, nbytes);
				
				break;
			}
			printf("Option not available\n---\n");
		}
	}

	//root = CompressTree (root);

	//PrintTable(root);

	root = DeletePrefix (root, "e");

	PrintTable(root);

	printf("Prefix %s Next-hop: %d\n", "11010011", LookUp (root, "11010011"));
	printf("Prefix %s Next-hop: %d\n", "11000011", LookUp (root, "11000011"));

	return 0;  
}

void print_usage(char *program)
{
	fprintf(stderr, "Usage: %s [-f input-file]\n", program);
	exit(1);
}