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
