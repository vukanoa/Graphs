#include "graph.h"

int
main()
{
	struct Node* first = connect_insert(NULL, 4);
	struct Node* second = connect_insert(first, 5);

	printf("\n\t%d -> %d\n\n", first->data, second->data);


	return 0;
}
