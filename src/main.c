#include <stdlib.h>
#include "di_graph.h"

int main()
{
	int num_edges = 8;
	struct Edge* edges = (struct Edge*) malloc (num_edges * sizeof(struct Edge));
	edges[0].source = 0;
	edges[0].destination = 1;
	
	edges[1].source = 1;
	edges[1].destination = 2;

	edges[2].source = 2;
	edges[2].destination = 0;

	edges[3].source = 2;
	edges[3].destination = 1;

	edges[4].source = 3;
	edges[4].destination = 2;

	edges[5].source = 4;
	edges[5].destination = 5;

	edges[6].source = 5;
	edges[6].destination = 4;

	edges[7].source = 3;
	edges[7].destination = 4;

	struct di_Graph* di_graph = create_di_graph(edges, num_edges);
	print_di_graph(di_graph);

	return 0;
}
