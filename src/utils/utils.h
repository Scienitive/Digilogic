#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void *malloc_or_die(size_t size);
void *realloc_or_die(void *ptr, size_t size);

#endif
