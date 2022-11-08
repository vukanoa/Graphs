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
DFS(struct di_Graph* di_graph, int node_data, int* visited)
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
BFS(struct di_Graph* di_graph, int node_data, int* visited)
{
	/* QUEUE */
	int max_size = V * (V - 1);
	// Every vertix points too all the other nodes -> V * (V - 1)
	struct Node** queue = (struct Node**) malloc(max_size * sizeof(struct Node*));
	int front = -1;
	int rear  = 0;

	visited[node_data] = 1;
	printf("%d ", node_data);

	struct Node* n = NULL;
	while (front < rear)
	{
		if (n == NULL) // Only First iteration
			n = di_graph->root[node_data];
		else
			n = di_graph->root[n->data];

		// Push all adjacent nodes to the Queue
		while (n != NULL)
		{
			queue[rear++] = n;
			n = n->next;
		}

		n = queue[++front];

		// Not NULL & already visited
		while (n != NULL && visited[n->data] == 1)
			n = queue[++front];

		if (n != NULL)
		{
			visited[n->data] = 1;
			printf("%d ", n->data);
		}
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


void
clear_visited(int* visited)
{
	for (int i = 0; i < V; i++)
		visited[i] = 0;
}


int 
route_between_nodes_wrapper(struct di_Graph* di_graph, int src, int dest, int* visited)
{
	int left  = route_between_nodes(di_graph, src, dest, visited);
	clear_visited(visited);
	int right = route_between_nodes(di_graph, dest, src, visited);

	if (left || right) // If either route exists(or both) -> return 1(DOES exist)
		return 1;

	return 0; // Route from either node does NOT exist
}


int
route_between_nodes(struct di_Graph* di_graph, int src, int dest, int* visited)
{
	/* BFS that returns true if it finds dest */

	/* QUEUE */
	int max_size = V * (V - 1);
	struct Node** queue = (struct Node**) malloc(max_size * sizeof(struct Node*));
	int front = -1;
	int rear  = 0;

	visited[src] = 1;
	if (src == dest)
		return 1; // Route exists

	struct Node* n = NULL;
	while (front < rear)
	{
		if (n == NULL) // Only First iteration
			n = di_graph->root[src];
		else
			n = di_graph->root[n->data];

		// Push all adjacent nodes to the Queue
		while (n != NULL)
		{
			if (n->data == dest)
				return 1; // Route exists

			queue[rear++] = n;
			n = n->next;
		}

		n = queue[++front];

		// Not NULL & already visited
		while (n != NULL && visited[n->data] == 1)
			n = queue[++front];

		if (n != NULL)
			visited[n->data] = 1;
	}

	return 0; // Route between nodes "source" and "destination" does NOT exist
}
