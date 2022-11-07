#ifndef _DI_GRAPH_H
#define _DI_GRAPH_H

#include <stdio.h>
#define V 10

struct Node{
	int data;
	struct Node* next;
};

struct di_Graph{
	struct Node* root[V];
};

struct Edge{
	int source;
	int destination;
};


// Graph functions
struct di_Graph* create_di_graph(struct Edge* edges, int num_edges);

// Graph Algorithms
void DFS(struct di_Graph* di_graph, int node_data, int* visited);


// Utility functions
void print_di_graph(struct di_Graph* di_graph);

#endif // _DI_GRAPH_H
