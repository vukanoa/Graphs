#include <stdlib.h>
#include "di_graph.h"

int main()
{
	int num_edges = 8;
	struct Edge edges[] =
	{
		{0, 5}, {0, 4}, {0, 1}, {1, 4}, {1, 3}, {2, 1}, {3, 4}, {3, 2}
	};

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
	return 0;
}
