#include <stdlib.h>
#include "di_graph.h"

/* Directed Graph Functions */
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


int
cyclic(struct di_Graph* di_graph, int V_in_graph)
{
	int *visited = (int *) calloc(V_in_graph, sizeof(int));

	for (int i = 0; i < V_in_graph; i++)
	{
		visited[i] = 1;
		struct Node* tmp = di_graph->root[i];

		while (tmp != NULL)
		{
			if (cyclic_util(di_graph, visited, tmp))
				return 1;

			tmp = tmp->next;
		}
		visited[i] = 0;
	}

	return 0;
}


/* Directed Graph Algorithms */
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


int*
Topological_sort(struct di_Graph* di_graph, int V_in_graph)
{
	// Base case
	if (di_graph == NULL)
	{
		printf("\n\tError: Graph is Empty!\n\n");
		exit(-1);
	}

	if (cyclic(di_graph, V_in_graph))
	{
		printf("\n\tError: This graph containes CYCLES. It's not a DAG => Topological Sort doesn't exist!\n\n");
		exit(-1);
	}

	int top = -1;
	int* stack   = (int *) calloc(V_in_graph, sizeof(int));
	int* visited = (int *) calloc(V_in_graph, sizeof(int));

	int* ordering = (int *) malloc(sizeof(int));

	for (int i = 0; i < V_in_graph; i++)
	{
		struct Node* tmp = di_graph->root[i];

		while (tmp != NULL)
		{
			if (!visited[tmp->data])
				DFS_Topological(di_graph, tmp->data, visited, stack, &top);

			tmp = tmp->next;
		}
	}

	int x = 0;
	ordering[x++] = 0; // Put "root" as first
	while (top >= 0)
	{
		ordering[x++] = stack[top];
		top--;
	}

	return ordering;
}


void
DFS_Topological(struct di_Graph* di_graph, int node_data, int* visited, int* stack, int* top)
{
	visited[node_data] = 1;

	struct Node* n = di_graph->root[node_data];
	while (n != NULL)
	{
		if (visited[n->data] != 1)
			DFS_Topological(di_graph, n->data, visited, stack, top);

		n = n->next;
	}

	stack[++(*top)] = node_data;
}


/* Utility Functions */
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
cyclic_util(struct di_Graph* di_graph, int* visited, struct Node* curr)
{
	if (visited[curr->data] == 1)
		return 1;

	visited[curr->data] = 1;
	struct Node* tmp = di_graph->root[curr->data];

	while (tmp != NULL)
	{
		if (cyclic_util(di_graph, visited, tmp))
			return 1;

		tmp = tmp->next;
	}

	visited[curr->data] = 0;

	return 0;
}


int
vertices(struct Edge* edges, int num_edges)
{
	int *exist = (int *) calloc(V, sizeof(int));
	int num_of_vertices = 0;

	for (int i = 0; i < num_edges; i++)
	{
		if (!exist[edges[i].source])
		{
			num_of_vertices++;
			exist[edges[i].source] = 1;
		}

		if (!exist[edges[i].destination])
		{
			num_of_vertices++;
			exist[edges[i].destination] = 1;
		}
	}

	return num_of_vertices;
}


/* Directed Graph Problems */
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
