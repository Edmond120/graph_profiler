#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "graphs.h"
#include "array_utils.h"

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

Node * create_node(int degree) {
	Node *node = (Node *) malloc(sizeof(Node));
	if (degree >= 0) {
		node->degree = degree;
		node->edges = (int *) malloc(degree * sizeof(int));
	}
	return node;
}

void free_node(Node *node) {
	free(node->edges);
	free(node);
}

FILE * showg_graph_stream(const char *filename) {
	int fd[2];
	pipe(fd);
	if (fork() == 0) {
		// if child
		close(fd[0]); // close read fd
		dup2(fd[1], 1);
		execlp("showg", "showg", filename, (char *) NULL);
		return NULL;
	} else {
		close(fd[1]); // close write fd
		return fdopen(fd[0], "r");
	}
}

// helper functions just for read_in_graph
static bool is_empty_line(int length, char * line) {
	return length <= 0 || (length == 1 && line[0] == '\n');
}

static int parse_edges(char *cursor, int *output, int length) {
	int degree = 0;
	while (length > degree && cursor != NULL && *cursor != '\0') {
		char c = *cursor;
		if (c == ' ' || c == ';' || c == '\n') {
			cursor++;
			continue;
		}
		int n;
		sscanf(cursor, "%d", &n);
		cursor = strchr(cursor, ' ');
		output[degree] = n;
		degree++;
	}
	return degree;
}
//
Graph * read_in_graph(FILE *file) {
	char * line = NULL;
	size_t line_mem = 0;
	ssize_t chars_read;
	int graph_num, order;
	Graph * graph = NULL;
	do {
		chars_read = getline(&line, &line_mem, file);
		if (is_empty_line(chars_read, line)) {
			if (graph == NULL) { continue; }
			free(line);
			return graph;
		}
		if (strstr(line, "Graph") == line) {
			int items = sscanf(line, "Graph %d, order %d.\n", &graph_num, &order);
			if (items != 2) { break; }
			graph = create_graph(order);
			continue;
		}
		int index;
		int items = sscanf(line, "%d", &index);
		if (items != 1) { break; }
		int edges[order];
		int degree = parse_edges(strchr(line, ':') + 1, edges, order);
		Node * node = graph->nodes[index];
		node->degree = degree;
		node->edges = (int *) malloc(sizeof(int) * degree);
		memcpy(node->edges, edges, degree * sizeof(int));
	} while (chars_read != -1);
	free(line);
	return NULL;
}

void print_graph(Graph *graph) {
	if (graph == NULL) {
		printf("NULL\n");
		return;
	}
	printf("Graph (order %d):\n", graph->order);
	for (int i = 0; i < graph->order; i++) {
		putchar('\t');
		print_node(graph->nodes[i]);
	}
}

void print_node(Node *node) {
	if (node == NULL) {
		printf("NULL\n");
		return;
	}
	printf("Node (edges: %d): ", node->degree);
	print_int_array(node->degree, node->edges);
}

void print_profile(Profile *profile) {
	if (profile == NULL) {
		printf("NULL\n");
		return;
	}
	printf("Profile (length: %d): ", profile->length);
	print_int_array(profile->length, profile->sequence);
}
