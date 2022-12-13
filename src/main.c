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

	struct BO_Graph* bo_graph = create_bo_graph(edges, num_edges);
	printf("\n\tGraph:\n");
	print_bo_graph(bo_graph);

	printf("\n");
	deallocate(bo_graph);

	return 0;
}
