#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

void print_int_array(int length, int *array);

/* Sorts array using a counting sort. The integers in the array must be
 * between 0 and bound (exclusive) */
void int_counting_sort(int bound, int length, int *array);

/* Just like int_counting_sort but the array will be in reverse order */
void int_counting_sort_rev(int bound, int length, int *array);

#endif
