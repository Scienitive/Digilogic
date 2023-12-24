#include "array.h"
#include <stdlib.h>
#include <string.h>

void init_array(Array *arr, size_t element_size) {
	arr->data = NULL;
	arr->size = 0;
	arr->capacity = 0;
	arr->element_size = element_size;
}

void push(Array *arr, const void *element) {
	if (arr->size >= arr->capacity) {
		arr->capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;
		arr->data = realloc(arr->data, arr->capacity * arr->element_size);
	}

	void *dest = (char *)arr->data + arr->size * arr->element_size;
	memcpy(dest, element, arr->element_size);
	arr->size++;
}

void *at(Array *arr, size_t index) {
	if (index < arr->size) {
		return (char *)arr->data + index * arr->element_size;
	} else {
		return NULL;
	}
}

void erase(Array *arr, size_t index) {
	if (index >= arr->size) {
		return;
	}

	void *to_erase = (char *)arr->data + index * arr->element_size;
	void *next_element = (char *)to_erase + arr->element_size;
	size_t bytes_to_move = (arr->size - index - 1) * arr->element_size;
	memmove(to_erase, next_element, bytes_to_move);
	arr->size--;
}

void free_array(Array *arr) {
	free(arr->data);
	arr->data = NULL;
	arr->size = 0;
	arr->capacity = 0;
}
