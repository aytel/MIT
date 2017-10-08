#include "mergesort.h"
#include <stdio.h>

void merge(void * base, size_t mid, size_t num, size_t size, int (*comp)(const void *, const void *)) {
	/*for (int i = 0; i < (int)num; i++)
		printf("%c ", *(char*)(base + i * size));
	printf("\n");*/
	char *p1 = (char*)base, *p2 = (char*)(base + mid * size), *l1 = p2, *l2 = (char *)(base + num * size);
	void *temp = (void*)malloc(num * size);
	char *p = (char*)temp;
	while (p1 != l1 || p2 != l2) {
		if (p1 == l1) {
			for (int i = 0; i < (int)size; i++)
				*p++ = *p2++;
			continue;
		}
		if (p2 == l2) {
			for (int i = 0; i < (int)size; i++)
				*p++ = *p1++;
			continue;
		}
		if (comp((void*)p1, (void*)p2) <= 0)
			for (int i = 0; i < (int)size; i++)
				*p++ = *p1++;
		else
			for (int i = 0; i < (int)size; i++)
				*p++ = *p2++;
		}
	p1 = (char*)base, p2 = (char*)temp;
	for (int i = 0; i < (int)(num * size); i++) 
		*p1++ = *p2++;
	/*for (int i = 0; i < (int)num; i++)
		printf("%c ", *(char*)(base + i * size));
	printf("\n");*/
	free(temp);
}

void mergesort(void * base, size_t num, size_t size, int (*comp)(const void *, const void *)) {
	/*for (int i = 0; i < (int)num; i++)
		printf("%c ", *(char*)(base + i * size));
	printf("\n");*/
	if (num < 2)
		return;
	size_t mid = num / 2;
	mergesort(base, mid, size, comp), mergesort(base + mid * size, num - mid, size, comp);
	merge(base, mid, num, size, comp);
}
