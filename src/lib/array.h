#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Array {
	void *data;
	size_t size;
	size_t capacity;
	size_t element_size;
} Array;

void init_array(Array *arr, size_t size);
void push_array(Array *arr, const void *element);
void *at_array(Array *arr, size_t index);
void erase_array(Array *arr, size_t index);
void free_array(Array *arr);

#endif
