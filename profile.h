#ifndef PROFILE_H
#define PROFILE_H

typedef struct {
	int * sequence;
	unsigned int n; // length of sequence
} Profile;

Profile * create_profile(unsigned int n);

void free_profile(Profile *p);

#endif
