#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "graphs.h"

typedef enum {
	Imax,
	Imin,
	Emax,
	Emin,
} N_profile_type;

/* Obtains an unsorted neighborhood_profile of N_profile_type from
 * graph. Remember to call free_profile on the return value; */
Profile * create_neighborhood_profile(Graph *graph, N_profile_type);

/* Like create_neighborhood_profile, but the output is sorted */
Profile * create_neighborhood_profile_sorted(Graph *graph, N_profile_type);

/* Returns the unsorted degree sequence of all the nodes around the
 * node at node_index. Writes the length of the sequence to the address
 * in the argument "length".
 * A call to free should be made on the return value. */
int * neighborhood_degree_sequence(Graph *graph, int node_index, int *length);

/* Like neighborhood_degree_sequence, but the output is sorted */
int * neighborhood_degree_sequence_sorted(Graph *graph, int node_index, int *length);
#endif
