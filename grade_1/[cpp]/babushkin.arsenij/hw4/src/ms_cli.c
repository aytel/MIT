#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

int int_cmp(const void * p1, const void * p2) {
	return *(int *)p1 - *(int *)p2;	
}

int char_cmp(const void * p1, const void * p2) {
	return *(char *)p1 - *(char *)p2;
}

int str_cmp(const void * p1, const void * p2) {
	return strcmp(*(char **)p1, *(char **)p2);
}

int main(int argc, char **argv) {

	if (argc == 2) {
		printf("\n");
		return 0;
	}

	if (!strcmp(argv[1], "int")) {
		int * arr = malloc((argc - 2) * sizeof(int));
		for (int i = 0; i < argc - 2; i++)
			arr[i] = atoi(argv[i + 2]);
		mergesort(arr, argc - 2, sizeof(int), int_cmp);
		for (int i = 0; i < argc - 2; i++)
			printf("%d ", arr[i]);
		free(arr);
	}

	if (!strcmp(argv[1], "char")) {
		char * arr = malloc((argc - 2) * sizeof(char));
		for (int i = 0; i < argc - 2; i++)
			arr[i] = *argv[i + 2];
		mergesort(arr, argc - 2, sizeof(char), char_cmp);
		for (int i = 0; i < argc - 2; i++)
			printf("%c ", arr[i]);
		free(arr);

	}

	if (!strcmp(argv[1], "str")) {
		char **arr = malloc((argc - 2) * sizeof(char *));
		for (int i = 0; i < argc - 2; i++)
			arr[i] = argv[i + 2];
		mergesort(arr, argc - 2, sizeof(char *), str_cmp);
		for (int i = 0; i < argc - 2; i++)
			printf("%s ", arr[i]);
		free(arr);

	}

	return 0;
}
