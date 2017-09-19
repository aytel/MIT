#include "str.h"
#include <stdio.h>

int test_cpy() {
	char dest[11] = "aba", src[8] = "abacaba";
	strcpy(dest, src);
	strcmp(dest, "abacaba");
}

int test_cmp1() {
	char str1[4] = "aba", str2[8] = "abacaba";
	return !strcmp(str1, str2);
}

int test_cmp2() {
	char str1[4] = "aba", str2[8] = "aba";
	return strcmp(str1, str2);
}

int test_cat() {
	char dest[11] = "aba", src[8] = "abacaba";
	strcat(dest, src);
	return strcmp(dest, "abaabacaba");
}

int test_len() {
	char dest[11] = "aba", src[8] = "abacaba";
	strcat(dest, src);
	return strlen(dest) == 10;
}
