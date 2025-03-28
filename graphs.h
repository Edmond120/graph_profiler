#ifndef GRAPHS_H
#define GRAPHS_H
#include <stdio.h>

typedef struct {
	int * sequence;
	unsigned int length;
} Profile;

/* Creates a profile with length n.
 * The sequence is zeroed */
Profile * create_profile(unsigned int n);

void free_profile(Profile *p);

typedef struct {
	int degree;
	// edges is an array where each number is a Graph.nodes index.
	int * edges;
} Node;

/* nodes points to a list of node pointers.
 * Each of those node pointers point to a single Node */
typedef struct {
	int order;
	Node ** nodes;
} Graph;

/* Creates a graph of a certain order without any edges and
 * uninitialized nodes. Should be freed with free_graph.
 * The nodes in the graph are also created, but their values are not
 * initialized. */
Graph * create_graph(int order);

void free_graph(Graph *graph);

/* Creates a node with degree and edges initialized.
 * If edge count is a negative number then degree and edges are not
 * initialized. Should be freed with free_node */
Node * create_node(int degree);

void free_node(Node *node);

/* Read in a single graph from file and creates it.
 * The arg file should be from showg_graph_stream or a file containing
 * the output of the executable showg.
 * This uses create_graph behind the scenes. */
Graph * read_in_graph(FILE *file);

/* Uses showg to parse a .g6 file and returns a FILE pointer to the
 * output */
FILE * showg_graph_stream(const char *filename);

/* If graph is NULL, then "NULL\n" will be printed */
void print_graph(Graph *graph);

/* If node is NULL, then "NULL\n" will be printed */
void print_node(Node *node);

/* If profile is NULL, then "NULL\n" will be printed */
void print_profile(Profile *profile);

#endif
