#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *malloc_or_die(size_t size) {
	void *malloc_return = malloc(size);
	if (!malloc_return && size) {
		fprintf(stderr, "Malloc Error: Couldn't allocate memory!");
		exit(-1);
	}
	return malloc_return;
}

void *realloc_or_die(void *ptr, size_t size) {
	void *realloc_return = realloc(ptr, size);
	if (!realloc_return && size) {
		fprintf(stderr, "Realloc Error: Couldn't allocate memory!");
		exit(-1);
	}
	return realloc_return;
}
