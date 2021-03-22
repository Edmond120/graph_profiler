#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct {
	int * sequence;
	unsigned int length;
} Profile;

Profile * create_profile(unsigned int n);

void free_profile(Profile *p);

typedef struct {
	int edge_count;
	// edges is an array where each number is a Graph.nodes index.
	int * edges;
} Node;

typedef struct {
	int order;
	Node ** nodes;
} Graph;

/* Creates a graph of a certain order without any edges and
 * uninitialized nodes. Should be freed with free_graph */
Graph * create_graph(int order);

void free_graph(Graph *graph);

/* Creates a node with a edge_count and edges initialized.
 * If edge count is a negative number then edge_count and edges are not
 * initialized. Should be freed with free_node */
Node * create_node(int edge_count);

void free_node(Node *node);

#endif
