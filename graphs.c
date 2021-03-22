#include <stdlib.h>
#include "graphs.h"

Profile * create_profile(unsigned int length) {
	Profile * profile = (Profile *) malloc(sizeof(Profile));
	profile->sequence = (int *) calloc(length, sizeof(int));
	profile->length = length;
	return profile;
}

void free_profile(Profile *p) {
	free(p->sequence);
	free(p);
}

Graph * create_graph(int order) {
	Graph *graph = (Graph *) malloc(sizeof(Graph));
	graph->order = order;
	graph->nodes = (Node **) malloc(order * sizeof(Node *));
	for (int i = 0; i < order; i++) {
		graph->nodes[i] = create_node(-1);
	}
	return graph;
}

void free_graph(Graph *graph) {
	for (int i = 0; i < graph->order; i++) {
		free_node(graph->nodes[i]);
	}
	free(graph->nodes);
	free(graph);
}

Node * create_node(int edge_count) {
	Node *node = (Node *) malloc(sizeof(Node));
	if (edge_count >= 0) {
		node->edge_count = edge_count;
		node->edges = (int *) malloc(edge_count * sizeof(int));
	}
	return node;
}

void free_node(Node *node) {
	free(node->edges);
	free(node);
}
