#include <stdlib.h>
#include "neighborhood.h"
#include "array_utils.h"

/* Helper function for find_Popular and find_Max_occur since
 * both the popular degree and the amount of occurrences can
 * be computed together.
 * Result for Max_occur will be written to *occurrences.
 * Result for Popular will be returned, if there is a tie the
 * bigger degree will be selected. */
static int find_Popular_h(int length, int *neighborhood_degrees, bool is_inclusive, int *occurrences) {
	if (length == 0) {
		return 0;
	}
	int max = array_max(length, neighborhood_degrees);
	int array_length = max + 1;
	int array[array_length];
	for (int i = 0; i < array_length; i++) array[i] = 0;

	for (int i = 0; i < length; i++) {
		int degree = neighborhood_degrees[i];
		array[degree]++;
	}

	int most_occurrences = 0;
	int popular_degree = -1;
	for (int i = 0; i < array_length; i++) {
		if (array[i] > most_occurrences) {
			most_occurrences = array[i];
			popular_degree = i;
		} else if (array[i] == most_occurrences) {
			if (i > popular_degree) {
				most_occurrences = array[i];
				popular_degree = i;
			}
		}
	}
	if (occurrences != NULL) { *occurrences = most_occurrences; }
	return popular_degree;
}

static int find_Max(int length, int *neighborhood_degrees, bool is_inclusive) {
	int max = 0;
	for (int i = 0; i < length; i++) {
		if (neighborhood_degrees[i] > max) {
			max = neighborhood_degrees[i];
		}
	}
	return max;
}

static int find_Min(int length, int *neighborhood_degrees, bool is_inclusive) {
	if (length <= 0) { return 0; }
	int min = neighborhood_degrees[0];
	for (int i = 1; i < length; i++) {
		if (neighborhood_degrees[i] < min) {
			min = neighborhood_degrees[i];
		}
	}
	return min;
}

static int find_Range(int length, int *neighborhood_degrees, bool is_inclusive) {
	int max = array_max(length, neighborhood_degrees);
	int min = array_min(length, neighborhood_degrees);
	return max - min;
}

static int find_Id(int length, int *neighborhood_degrees, bool is_inclusive) {
	int self_degree;
	if (is_inclusive) {
		self_degree = length - 1;
	} else {
		self_degree = length;
	}
	return array_occurrences(length, neighborhood_degrees, self_degree);
}

static int find_Sum(int length, int *neighborhood_degrees, bool is_inclusive) {
	return array_sum(length, neighborhood_degrees);
}

static int find_Different(int length, int *neighborhood_degrees, bool is_inclusive) {
	int max = array_max(length, neighborhood_degrees);
	int array_length = max + 1;
	int array[array_length];
	for (int i = 0; i < array_length; i++) array[i] = 0;

	for (int i = 0; i < length; i++) {
		int degree = neighborhood_degrees[i];
		array[degree]++;
	}

	int diff = 0;
	for (int i = 0; i < array_length; i++) {
		if (array[i] > 0) {
			diff++;
		}
	}
	return diff;
}

/* Will return the bigger degree if there is a tie. */
static int find_Popular(int length, int *neighborhood_degrees, bool is_inclusive) {
	return find_Popular_h(length, neighborhood_degrees, is_inclusive, NULL);
}

/* Returns the amount of occurrences of the most popular degree in the neighborhood */
static int find_Max_occur(int length, int *neighborhood_degrees, bool is_inclusive) {
	int occurrences;
	find_Popular_h(length, neighborhood_degrees, is_inclusive, &occurrences);
	return occurrences;
}

/* The exclusive Degree profile is just the degree sequence, this option is just
 * included here for convenience. */
static int find_Degree(int length, int *neighborhood_degrees, bool is_inclusive) {
	return length;
}

Profile * create_neighborhood_profile(Graph *graph, N_profile_type type, bool is_inclusive) {
	int (*profile_func)(int ,int *, bool);
	switch (type) {
		case Max:
			profile_func = find_Max;
			break;
		case Min:
			profile_func = find_Min;
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
		case Different:
			profile_func = find_Different;
			break;
		case Popular:
			profile_func = find_Popular;
			break;
		case Max_occur:
			profile_func = find_Max_occur;
			break;
		case Degree:
			profile_func = find_Degree;
			break;
		default:
			return NULL;
	}
	Profile *profile = create_profile(graph->order);
	for (int i = 0; i < graph->order; i++) {
		int length;
		int *degree_seq = neighborhood_degree_sequence(graph, i, &length, is_inclusive);
		profile->sequence[i] = (*profile_func)(length, degree_seq, is_inclusive);
		free(degree_seq);
	}
	return profile;
}

Profile * create_neighborhood_profile_sorted(Graph *graph, N_profile_type type, bool is_inclusive) {
	Profile *profile = create_neighborhood_profile(graph, type, is_inclusive);
	int max = array_max(profile->length, profile->sequence);
	int_counting_sort_rev(max, profile->length, profile->sequence);
	return profile;
}

int * neighborhood_degree_sequence(Graph *graph, int node_index, int *length, bool is_inclusive) {
	Node *node = graph->nodes[node_index];
	*length = node->degree;
	if (is_inclusive) {
		*length += 1;
	}
	int *deg_seq = (int *) calloc(*length, sizeof(int));
	for (int i = 0; i < node->degree; i++) {
		int *edges = node->edges;
		Node *neighbor = graph->nodes[edges[i]];
		int degree = neighbor->degree;
		deg_seq[i] = degree;
	}
	if (is_inclusive) {
		deg_seq[*length - 1] = node->degree;
	}
	return deg_seq;
}

int * neighborhood_degree_sequence_sorted(Graph *graph, int node_index, int *length, bool is_inclusive) {
	int * deg_seq = neighborhood_degree_sequence(graph, node_index, length, is_inclusive);
	int_counting_sort_rev(graph->order, *length, deg_seq);
	return deg_seq;
}
