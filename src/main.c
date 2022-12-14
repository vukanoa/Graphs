#include <stdlib.h>
#include "di_graph.h"
#include "build_order.h"


int main()
{
	int num_edges = 8;
	struct BO_Edge edges[] =
	{
		{'f', 'c'}, {'f', 'a'}, {'f', 'b'}, {'c', 'a'}, {'b', 'a'}, {'b', 'e'}, {'a', 'e'}, {'d', 'g'}
	};

	printf("\n\t===================");
	printf("\n\t=== BUILD ORDER ===");
	printf("\n\t===================\n\n");

	struct BO_Graph* bo_graph = create_bo_graph(edges, num_edges);
	printf("\n\tGraph:\n");
	print_bo_graph(bo_graph);

	/* Dependencies */
	// printf("\n\tHow many projects have to be built before:");
	// for (int i = 0; i < MAX_VERTICES; i++)
	// 	printf("\n\t%c: %d", i + 97, bo_graph->dependencies[i]);

	int used_vertices = projects_number(edges, num_edges);
	// printf("\n\tUsed vertices: %d\n", used_vertices);

	char* order = build_order(bo_graph, used_vertices);
	printf("\n\t");

	printf("\n\tBUILD ORDER:\n\t\t");
	for (int i = 0; i < used_vertices; i++)
		printf("%c ", order[i]);

	printf("\n\n\n");

	/* Deallocate */
	deallocate(bo_graph);
	free(order);

	return 0;
}
