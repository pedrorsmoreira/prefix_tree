#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "api.h"

void print_usage(char*);

int main(int argc, char *argv[]) 
{ 
	int opt;
	bool isCompressed = false;
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

	// Create table
	Node* _root = PrefixTree (filename), *Croot, *root;

	while(1) {
		//read the action from stdin and perform it
		while (1) {
		char order, aux[50], prefix[50], nexthop[50];
			if (isCompressed) {
				printf("(Enter [Q] to quit)\nIntroduce the tree to act on: Non-Compressed [N], Compressed [C]: ");
				if (fgets(aux, sizeof(aux), stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				sscanf(aux, "%c", &order);
				if ((order == 'q') || (order == 'Q'))
					return 0;
				else if (order == 'n' || order == 'N')
					root = _root;
				else if (order == 'c' || order == 'C')
					root = Croot;
				else {
					printf("Option not available\n---\n");
					continue;
				}
				printf("\n---\n\n");
			} 
			else 
				root = _root;

			printf("(Enter [Q] to quit)\nIntroduce the action, Print [P], Search [S], Insert [I], Delete [D] or Compress [C]: ");
			if (fgets(aux, sizeof(aux), stdin) == NULL) {
				perror("fgets: ");
				exit(-1);
			}
			sscanf(aux, "%c", &order);
			//perform
			if ((order == 'q') || (order == 'Q'))
				return 0;
			else if ((order == 'i') || (order == 'I')){
				printf("Write the prefix to be inserted: ");	
				if (fgets(prefix, 50, stdin) == NULL){
					perror("fgets: ");
					exit(-1);
				}
				prefix[strlen(prefix)-1] = '\0';
				printf("Write the nexthop: ");	
				if (fgets(nexthop, 50, stdin) == NULL) {
					perror("fgets: ");
					exit(-1);
				}
				nexthop[strlen(nexthop)-1] = '\0';
				root = InsertPrefix(root, prefix, atoi(nexthop));

				printf("\n---\n\n");

				break;
			}
			else if ((order == 'P') || (order == 'p')) {
				PrintTable(root);
				printf("\n---\n\n");
				break;
			}
			else if ((order == 'S') || (order == 's')) {
				printf("Write the address where to Look up for the next hop: ");	
				if (fgets(prefix, 50, stdin) == NULL) {
					perror("fgets: ");
					exit(-1);
				}
				prefix[strlen(prefix)-1] = '\0';
				int nh = LookUp(root, prefix);
				if (nh < 0)
					printf("Wrong address.\n \n---\n\n");
				else
					printf("Next hop: %d.\n \n---\n\n", nh);
				
				break;
			}
			else if ((order == 'D') || (order == 'd')) {
				printf("Write the prefix to be deleted: ");	
				if (fgets(prefix, 50, stdin) == NULL) {
					perror("fgets: ");
					exit(-1);
				}
				prefix[strlen(prefix)-1] = '\0';
				root = DeletePrefix (root, prefix);

				printf("\n---\n\n");

				break;
			}
			else if ((order == 'C') || (order == 'c')) {
				if (isCompressed) {
					if (root == Croot) {
						printf("Tree already compressed.\n---\n\n");
						break;
					}
					else
						clean(Croot);
				}
				Croot = CompressTree(root);
				isCompressed = true;
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