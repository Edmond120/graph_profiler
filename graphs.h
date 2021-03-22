#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct {
	int * sequence;
	unsigned int length;
} Profile;

Profile * create_profile(unsigned int n);

void free_profile(Profile *p);

#endif
