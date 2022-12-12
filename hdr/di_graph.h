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
int cyclic(struct di_Graph* di_graph, int V_in_graph);


// Graph Algorithms
void DFS(struct di_Graph* di_graph, int node_data, int* visited);
void BFS(struct di_Graph* di_graph, int node_data, int* visited);

int* Topological_sort(struct di_Graph* di_graph, int V_in_graph);
void DFS_Topological(struct di_Graph* di_graph, int node_data, int* visited, int* stack, int* top);


// Utility functions
void print_di_graph(struct di_Graph* di_graph);
void clear_visited (int* visited);
int  cyclic_util   (struct di_Graph* di_Graph, int* visited, struct Node* curr);
int  vertices      (struct Edge* edges, int num_edges);


// Graph Problems
int route_between_nodes_wrapper(struct di_Graph* di_graph, int src, int dest, int* visited);
int route_between_nodes        (struct di_Graph* di_graph, int src, int dest, int* visited);

#endif // _DI_GRAPH_H
