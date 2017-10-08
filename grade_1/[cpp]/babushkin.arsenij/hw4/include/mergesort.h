#ifndef MERGE
#define MERGE
#include <stddef.h>
#include <stdlib.h>

void mergesort(void * base, size_t num, size_t size, int (*comp)(const void *, const void *));

#endif
