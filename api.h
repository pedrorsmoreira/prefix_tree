
struct node* PrefixTree (char* filename);

struct node* InsertPrefix (struct node* root, char prefix[], size_t nextHop);

size_t LookUp (struct node* root, char addr[]);

void PrintTable (struct node* root);

struct node* DeletePrefix (struct node* root, char* prefix);