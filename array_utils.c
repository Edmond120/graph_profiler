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

void int_counting_sort(int bound, int length, int *array) {
	int counts[bound] = {0};
	for (int i = 0; i < length; i++) {
		counts[array[i]] += 1;
	}
	int index = length - 1;
	int n = bound - 1;
	while (n >= 0 && index >= 0) {
		for (int i = 0; i < counts[n]; i++) {
			array[index--] = n;
		}
		n--;
	}
}
