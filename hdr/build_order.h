#ifndef _BUILD_ORDER_H_
#define _BUILD_ORDER_H_

#include<stdio.h>
#define MAX_VERTICES 10

// BO - Build Order
struct BO_Node{
	char letter;
	struct BO_Node* next;
};

struct BO_Graph{
	int* dependencies;
	struct BO_Node* root[MAX_VERTICES];
};

struct BO_Edge{
	char source;
	char destination;
};


// Build Order Graph functions
struct BO_Graph* create_bo_graph(struct BO_Edge*  edges, int num_edges);

// char* build_order      (struct BO_Graph* bo_graph, int used_vertices);
void  deallocate       (struct BO_Graph* bo_graph);
// int   add_non_dependent(struct BO_Graph* bo_graph, char* ordering, int offset, int vertices);

// Utility functions
void print_bo_graph(struct BO_Graph* bo_graph);
int  project_number(struct BO_Edge*  edges, int num_edges);

#endif // _BUILD_ORDER_H_
