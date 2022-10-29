#include <stdlib.h>
#include "graph.h"

struct Node*
connect_insert(struct Node* node, int data)
{
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->data = data;
	new_node->next = NULL;

	new_node->next = node;

	return new_node;
}
