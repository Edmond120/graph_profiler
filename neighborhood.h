#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <stdbool.h>
#include "graphs.h"

typedef enum {
	Max,
	Min,
	Range,
	Id,
	Sum,
	Different,
	Popular,
} N_profile_type;

/* Obtains an unsorted neighborhood_profile of N_profile_type from
 * graph. Remember to call free_profile on the return value; */
Profile * create_neighborhood_profile(Graph *graph, N_profile_type, bool is_inclusive);

/* Like create_neighborhood_profile, but the output is sorted */
Profile * create_neighborhood_profile_sorted(Graph *graph, N_profile_type, bool is_inclusive);

/* Returns the unsorted degree sequence of all the nodes around the
 * node at node_index. Writes the length of the sequence to the address
 * in the argument "length".
 * The return array is essentially the degree sequence of the node's
 * exclusive neighborhood.
 * A call to free should be made on the return value. */
int * neighborhood_degree_sequence(Graph *graph, int node_index, int *length, bool is_inclusive);

/* Like neighborhood_degree_sequence, but the output is sorted */
int * neighborhood_degree_sequence_sorted(Graph *graph, int node_index, int *length, bool is_inclusive);
#endif
