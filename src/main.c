#include <stdlib.h>
#include "di_graph.h"


int main()
{
	/* No cycle => Topological Sort exists */
	int num_edges = 8;
	struct Edge edges[] =
	{
		{0, 5}, {0, 4}, {0, 1}, {1, 3}, {1, 4}, {3, 4}, {3, 2}, {5, 3}
	};

	/* Cycle => No Topological Sort */
	// int num_edges = 9;
	// struct Edge edges[] =
	// {
	// 	{0, 5}, {0, 4}, {0, 1}, {1, 3}, {1, 4}, {2, 1}, {3, 4}, {3, 2}, {5, 3}
	// };

	int *visited = (int *) calloc(V, sizeof(int));

	struct di_Graph* di_graph = create_di_graph(edges, num_edges);
	printf("\n\tGraph:\n");
	print_di_graph(di_graph);

	printf("\n\tDFS:\n\t\t");
	DFS(di_graph, 0, visited);
	printf("\n\n");

	clear_visited(visited);

	printf("\n\tBFS:\n\t\t");
	BFS(di_graph, 0, visited);
	printf("\n\n");

	clear_visited(visited);

	/* Route Between Nodes */
	int source_node = 3;
	int destination_node = 0;
	printf("\n\tSolution: ");
	int sol = route_between_nodes(di_graph, source_node, destination_node, visited);
	if (sol)
		printf("\n\t\tRoute between Nodes: %d & %d DOES exist!\n\n", source_node, destination_node);
	else
		printf("\n\t\tRoute between Nodes: %d & %d does NOT exist!\n\n", source_node, destination_node);

	/*
		In this directed graph, route between 3 & 0 does NOT exist.
		However route from 0 to 3 DOES exist - therefore a route between these
		2 nodes do exist.

		But since this is DG(Not DAG currently), we will say that route
		from 3 to 0 does NOT exist.
	*/

	printf("\n\tNumber of Vertices: %d\n", vertices(edges, num_edges));

	int num_of_vertices = vertices(edges, num_edges);
	if (cyclic(di_graph, num_of_vertices))
		printf("\n\tThis graph does INDEED contain a cycle! It's not a DAG!\n\n");
	else
		printf("\n\tThis graph does NOT contain a cycle! It is a DAG!\n\n");


	int* ordering = (int *) malloc(sizeof(int));
	ordering = Topological_sort(di_graph, num_of_vertices);

	printf("\n\tTopological Sort:\n\t\t");
	for (int i = 0; i < num_of_vertices; i++)
		printf("%d ", ordering[i]);

	printf("\n\n");

	return 0;
}
