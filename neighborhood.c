#include <stdlib.h>

Profile * create_profile(unsigned int n) {
	Profile * profile = (Profile *) malloc(sizeof(Profile));
	profile->sequence = (int *) calloc(n, sizeof(int));
	profile->n = n;
	return profile;
}

void free_profile(Profile *p) {
	free(p->sequence);
	free(p);
}
