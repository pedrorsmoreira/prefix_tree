#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() 
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

	return 0;  
}