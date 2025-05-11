/**
 * -------------------------------------
 * @file  min_heap.c
 * Minimum Heap Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2024-03-11
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "min_heap.h"

#define STRING_SIZE 80

// local functions

/**
 * Swaps two data values.
 *
 * @param a pointer to data.
 * @param b pointer to data.
 */
static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/**
 * Moves the last value in source until it is in its correct location
 * in source.
 *
 * @param source - pointer to a heap
 */
static void heapify_up(min_heap *source) {
	//Data being inserted is {11, 7, 15, 6, 9, 12, 18, 8}
    // your code here
	int last_index = source->count - 1;
	int parent_index = (last_index - 1) / 2;
	while (last_index > 0
			&& source->values[parent_index] > source->values[last_index]) {
		int temp_value = source->values[last_index];
		source->values[last_index] = source->values[parent_index];
		source->values[parent_index] = temp_value;

		last_index = parent_index;
		parent_index = (last_index - 1) / 2;
	}
    return;
}

/**
 * Moves a value down source to its correct position.
 *
 * @param source - pointer to a heap
 */
static void heapify_down(min_heap *source) {

    // your code here
	int parent_index = 0;
	int left_child_index = (2 * parent_index + 1);
	int right_child_index = (2 * parent_index + 2);
	while (left_child_index < source->count) {
		int lower_child_index = left_child_index;
		if (right_child_index < source->count
				&& source->values[right_child_index]
						< source->values[left_child_index]) {
			lower_child_index = right_child_index;
		}
		if (source->values[lower_child_index] < source->values[parent_index]) {
			int temp_value = source->values[lower_child_index];
			source->values[lower_child_index] = source->values[parent_index];
			source->values[parent_index] = temp_value;
			parent_index = lower_child_index;
			left_child_index = (2 * parent_index + 1);
			right_child_index = (2 * parent_index + 2);
		} else
			break;
	}
    return;
}

// Public minimum heap functions

min_heap* min_heap_initialize(int capacity) {
    min_heap *source = malloc(sizeof *source);
    source->values = malloc(capacity * sizeof *source->values);
    source->capacity = capacity;
    source->count = 0;
    return source;
}

void min_heap_free(min_heap **source) {
    free((*source)->values);
    free(*source);
    *source = NULL;
    return;
}

void min_heap_heapify(min_heap *source, int *keys, int count) {

    for(int i = 0; i < count; i++) {
        min_heap_insert(source, keys[i]);
    }
    return;
}

int min_heap_empty(const min_heap *source) {
    return (source->count == 0);
}

int min_heap_full(const min_heap *source) {
    return (source->count == source->capacity);
}

int min_heap_count(const min_heap *source) {
    return (source->count);
}

void min_heap_insert(min_heap *source, const int value) {
    // Add new value to end of the heap.
    source->values[source->count] = value;
    source->count++;
    // Fix the heap.
    heapify_up(source);
    return;
}

int min_heap_peek(const min_heap *source) {
    return (source->values[0]);
}

int min_heap_remove(min_heap *source) {
    int value = source->values[0];
    source->count--;

    if(source->count > 0) {
        // Move last value to top of heap.
        source->values[0] = source->values[source->count];
        // Fix the heap.
        heapify_down(source);
    }
    return value;
}

int min_heap_valid(const min_heap *source) {

    // your code here
	int n = source->count;
	for (int i = 0; i <= (n - 2) / 2; i++) {
		if (2 * i + 1 < n && source->values[i] > source->values[2 * i + 1]) {
			return 0;
		}
		if (2 * i + 2 < n && source->values[i] > source->values[2 * i + 2]) {
			return 0;
		}
	}
	return 1;
}

int min_heap_replace(min_heap *source, int replacement) {
    int value = source->values[0];
    source->values[0] = replacement;
    heapify_down(source);
    return value;
}

static void heap_sort_aux(int *values, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && values[left] > values[largest]) {
		largest = left;
	}
	if (right < n && values[right] > values[largest]) {
		largest = right;
	}
	if (largest != i) {
		int temp = values[i];
		values[i] = values[largest];
		values[largest] = temp;
		heap_sort_aux(values, n, largest);
	}
	return;
}

void heap_sort(int *values, int count) {

    // your code here
	for (int i = count / 2 - 1; i >= 0; i--) {
		heap_sort_aux(values, count, i);
	}

	for (int i = count - 1; i > 0; i--) {
		int temp = values[0];
		values[0] = values[i];
		values[i] = temp;
		heap_sort_aux(values, i, 0);
	}

    return;
}

// for testing
void min_heap_print(const min_heap *source) {
    printf("{");

    for(int i = 0; i < source->count; i++) {
        printf("%d, ", source->values[i]);
    }
    printf("}\n");
    return;
}
