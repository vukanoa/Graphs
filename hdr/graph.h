#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>

struct Node{
	int data;
	struct Node* next;
};

struct Node* connect_insert(struct Node* node, int data);

#endif // GRAPH_H_
