#include <stdlib.h>
#include "di_graph.h"

struct di_Graph*
create_di_graph(struct Edge* edges, int num_edges)
{
	struct di_Graph* di_graph = (struct di_Graph*) malloc (sizeof(struct di_Graph));

	for (int i = 0; i < V; i++)
		di_graph->root[i] = NULL;

	for (int i = 0; i < num_edges; i++)
	{
		int source      = edges[i].source;
		int destination = edges[i].destination;

		struct Node* node = (struct Node*) malloc (sizeof(struct Node));
		node->data = destination;

		// Put in Graph's Adjacent List for the source index
		node->next = di_graph->root[source];
		di_graph->root[source] = node;
	}

	return di_graph;
}


void
print_di_graph(struct di_Graph* di_graph)
{
	printf("\n");
	for (int i = 0; i < V; i++)
	{
		struct Node* node = di_graph->root[i];
		if (node != NULL)
		{
			printf("\t");
			while (node != NULL)
			{
				printf("(%d -> %d) ", i, node->data);
				node = node->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}
