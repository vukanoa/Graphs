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


void DFS(struct di_Graph* di_graph, int node_data, int* visited)
{
	// Base case
	if (di_graph == NULL)
		return;

	visited[node_data] = 1;
	printf("%d ", node_data);

	struct Node* n = di_graph->root[node_data];
	while (n != NULL)
	{
		if (visited[n->data] != 1)
			DFS(di_graph, n->data, visited);

		n = n->next;
	}
}


void
print_di_graph(struct di_Graph* di_graph)
{
	for (int i = 0; i < V; i++)
	{
		struct Node* node = di_graph->root[i];
		if (node != NULL)
		{
			printf("\t\t");
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
