#include <stdlib.h>
#include "neighborhood.h"
#include "array_utils.h"

static int find_Imax(int length, int *neighborhood_degrees) {
	int max = length;
	for (int i = 0; i < length; i++) {
		if (neighborhood_degrees[i] > max) {
			max = neighborhood_degrees[i];
		}
	}
	return max;
}

static int find_Imin(int length, int *neighborhood_degrees) {
	if (length <= 0) { return 0; }
	int min = neighborhood_degrees[0];
	for (int i = 1; i < length; i++) {
		if (neighborhood_degrees[i] < min) {
			min = neighborhood_degrees[i];
		}
	}
	if (length < min) {
		min = length;
	}
	return min;
}

/* This function uses an exclusive neighborhood */
static int find_Emax(int length, int *neighborhood_degrees) {
	int max = 0;
	for (int i = 0; i < length; i++) {
		if (neighborhood_degrees[i] > max) {
			max = neighborhood_degrees[i];
		}
	}
	return max;
}

/* This function uses an exclusive neighborhood */
static int find_Emin(int length, int *neighborhood_degrees) {
	if (length <= 0) { return 0; }
	int min = neighborhood_degrees[0];
	for (int i = 1; i < length; i++) {
		if (neighborhood_degrees[i] < min) {
			min = neighborhood_degrees[i];
		}
	}
	return min;
}

/* This function uses an exclusive neighborhood */
static int find_Range(int length, int *neighborhood_degrees) {
	int max = array_max(length, neighborhood_degrees);
	int min = array_min(length, neighborhood_degrees);
	return max - min;
}

/* This function uses an exclusive neighborhood */
static int find_Id(int length, int *neighborhood_degrees) {
	return array_occurences(length, neighborhood_degrees, length);
}

/* This function uses an exclusive neighborhood */
static int find_Sum(int length, int *neighborhood_degrees) {
	return array_sum(length, neighborhood_degrees);
}

Profile * create_neighborhood_profile(Graph *graph, N_profile_type type) {
	int (*profile_func)(int ,int *);
	switch (type) {
		case Imax:
			profile_func = find_Imax;
			break;
		case Imin:
			profile_func = find_Imin;
			break;
		case Emax:
			profile_func = find_Emax;
			break;
		case Emin:
			profile_func = find_Emin;
			break;
		case Range:
			profile_func = find_Range;
			break;
		case Id:
			profile_func = find_Id;
			break;
		case Sum:
			profile_func = find_Sum;
			break;
		default:
			return NULL;
	}
	Profile *profile = create_profile(graph->order);
	for (int i = 0; i < graph->order; i++) {
		int length;
		int *degree_seq = neighborhood_degree_sequence(graph, i, &length);
		profile->sequence[i] = (*profile_func)(length, degree_seq);
		free(degree_seq);
	}
	return profile;
}

Profile * create_neighborhood_profile_sorted(Graph *graph, N_profile_type type) {
	Profile *profile = create_neighborhood_profile(graph, type);
	int_counting_sort_rev(profile->length, profile->length, profile->sequence);
	return profile;
}

int * neighborhood_degree_sequence(Graph *graph, int node_index, int *length) {
	Node *node = graph->nodes[node_index];
	int *deg_seq = (int *) calloc(node->degree, sizeof(int));
	*length = node->degree;
	for (int i = 0; i < node->degree; i++) {
		int *edges = node->edges;
		Node *neighbor = graph->nodes[edges[i]];
		int degree = neighbor->degree;
		deg_seq[i] = degree;
	}
	return deg_seq;
}

int * neighborhood_degree_sequence_sorted(Graph *graph, int node_index, int *length) {
	int * deg_seq = neighborhood_degree_sequence(graph, node_index, length);
	int_counting_sort_rev(graph->order, *length, deg_seq);
	return deg_seq;
}
