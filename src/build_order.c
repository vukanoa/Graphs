#include <stdlib.h>
#include "build_order.h"

#define LOWERCASE_A 97

/* Build Order Graph Functions */
struct BO_Graph*
create_bo_graph(struct BO_Edge* edges, int num_edges)
{
	struct BO_Graph* bo_graph = (struct BO_Graph*) malloc (sizeof(struct BO_Graph));

	bo_graph->dependencies = (int*) calloc(MAX_VERTICES, sizeof(int));
	for (int i = 0; i < MAX_VERTICES; i++)
		bo_graph->root[i] = NULL;

	for (int i = 0; i < num_edges; i++)
	{
		char source      = edges[i].source;
		char destination = edges[i].destination;

		struct BO_Node* node = (struct BO_Node*) malloc (sizeof(struct BO_Node));
		node->letter = destination;

		// Put in Graph's Adjacent List for the source index
		node->next = bo_graph->root[source - LOWERCASE_A];
		bo_graph->root[source - LOWERCASE_A] = node;
		bo_graph->dependencies[destination - LOWERCASE_A]++;
	}

	return bo_graph;
}


char*
build_order(struct BO_Graph* bo_graph, int used_vertices)
{
	char* order = (char*) calloc(used_vertices, sizeof(char));
	char projects[used_vertices];

	for (int i = 0; i < used_vertices; i++)
		projects[i] = i + LOWERCASE_A;

	/* add "roots" to the build order first */
	int end_of_list = add_non_dependent(bo_graph, projects, 0, used_vertices, order);

	int to_be_processed = 0;
	while (to_be_processed < used_vertices)
	{
		char current = order[to_be_processed];

		/*
			We have a circular dependency since there are no remaining projects
			with zero dependencies
		*/
		if (current == 0)
			return NULL;

		char children[MAX_VERTICES];

		/* Remove myself from a dependency */
		struct BO_Node* child = bo_graph->root[current - LOWERCASE_A];
		int i = 0;

		while (child != NULL)
		{
			bo_graph->dependencies[child->letter - LOWERCASE_A]--;
			children[i++] = child->letter;

			child = child->next;
		}

		end_of_list = add_non_dependent(bo_graph, children, end_of_list, i, order);
		to_be_processed++;
	}

	return order;
}


int
add_non_dependent(struct BO_Graph* bo_graph, char* projects, int offset, int projects_size, char* order)
{
	for (int i = 0; i < projects_size; i++)
	{
		if (bo_graph->dependencies[projects[i] - LOWERCASE_A] == 0)
		{
			order[offset] = projects[i];
			offset++;
		}
	}

	return offset;
}


void
deallocate(struct BO_Graph* bo_graph)
{
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		struct BO_Node* node = bo_graph->root[i];

		while (node != NULL)
		{
			struct BO_Node* tmp  = node;

			node = node->next;
			free(tmp);
		}
	}

	free(bo_graph->dependencies);
	free(bo_graph);
}


/* Utility Functions */
void
print_bo_graph(struct BO_Graph* bo_graph)
{
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		struct BO_Node* node = bo_graph->root[i];
		if (node != NULL)
		{
			printf("\t\t");
			while (node != NULL)
			{
				printf("(%c -> %c) ", i + LOWERCASE_A, node->letter);
				node = node->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}


int
projects_number(struct BO_Edge* edges, int num_edges)
{
	int *exist = (int *) calloc(MAX_VERTICES, sizeof(int));
	int num_of_vertices = 0;

	for (int i = 0; i < num_edges; i++)
	{
		if (!exist[edges[i].source - LOWERCASE_A])
		{
			num_of_vertices++;
			exist[edges[i].source - LOWERCASE_A] = 1;
		}

		if (!exist[edges[i].destination - LOWERCASE_A])
		{
			num_of_vertices++;
			exist[edges[i].destination - LOWERCASE_A] = 1;
		}
	}
	free(exist);

	return num_of_vertices;
}
