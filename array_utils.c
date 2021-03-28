#include <stdio.h>
#include <string.h>
#include "array_utils.h"

void print_int_array(int length, int *array) {
	for (int i = 0; i < length - 1; i++) {
		printf("%d", array[i]);
		printf(", ");
	}
	if (length > 0) {
		printf("%d\n", array[length - 1]);
	}
}

void int_counting_sort(int bound, int length, int *array) {
	int counts[bound];
	memset(counts, 0, bound * sizeof(int));
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

void int_counting_sort_rev(int bound, int length, int *array) {
	int counts[bound];
	memset(counts, 0, bound * sizeof(int));
	for (int i = 0; i < length; i++) {
		counts[array[i]] += 1;
	}
	int index = length - 1;
	int n = 0;
	while (n < bound && index >= 0) {
		for (int i = 0; i < counts[n]; i++) {
			array[index--] = n;
		}
		n++;
	}
}

int array_min(int length, int *array) {
	if (length <= 0) { return 0; }
	int min = array[0];
	for (int i = 1; i < length; i++) {
		if (array[i] < min) {
			min = array[i];
		}
	}
	return min;
}

int array_max(int length, int *array) {
	if (length <= 0) { return 0; }
	int max = array[0];
	for (int i = 1; i < length; i++) {
		if (array[i] > max) {
			max = array[i];
		}
	}
	return max;
}

int array_occurences(int length, int *array, int num) {
	int occurences = 0;
	for (int i = 0; i < length; i++) {
		if (array[i] == num) {
			occurences++;
		}
	}
	return occurences;
}
