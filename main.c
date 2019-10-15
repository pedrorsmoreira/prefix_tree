#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	while(1){
		//read the action from stdin and perform it
		while (1){
		char order, aux[50], prefix[16+1], nexthop[16+1];
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
				if (fgets(prefix, 16+1, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				prefix[strlen(prefix)-1] = '\0';
				printf("Write the nexthop:");	
				if (fgets(nexthop, 16+1, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				nexthop[strlen(nexthop)-1] = '\0';
				root = InsertPrefix(root, prefix, atoi(nexthop));

				printf("\n---\n\n");

				break;
			}
			else if ((order == 'P') || (order == 'p')){
				PrintTable(root);
				printf("\n---\n\n");
				break;
			}
			else if ((order == 'S') || (order == 's')){
				printf("Write the prefix where to Look up for the next hop:");	
				if (fgets(prefix, 16+1, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				printf("next hop: %d.\n \n---\n\n", LookUp(root, prefix));
				
				break;
			}
			else if ((order == 'D') || (order == 'd')){
				printf("Write the prefix to be deleted:");	
				if (fgets(prefix, 16+1, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				prefix[strlen(prefix)-1] = '\0';
				root = DeletePrefix (root, prefix);

				printf("\n---\n\n");

				break;
			}
			else if ((order == 'C') || (order == 'c')){
				root = CompressTree(root);
				printf("Tree compressed.\n---\n\n");
				break;
			}
			printf("Option not available\n---\n");
		}
	}

	return 0;  
}

void print_usage(char *program)
{
	fprintf(stderr, "Usage: %s [-f input-file]\n", program);
	exit(1);
}