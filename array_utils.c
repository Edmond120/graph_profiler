#include <stdio.h>
#include "array_utils.h"

void print_int_array(int length, int *array) {
	for (int i = 0; i < length; i++) {
		printf("%d", array[i]);
		if (i != length - 1) {
			printf(", ");
		}
	}
	putchar('\n');
}
