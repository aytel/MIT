#include "str.h"

char * strcpy (char * dest, char * src) {
	char * p = dest;
	while (*src) 
		*p++ = *src++;
	*p = *src;
	return dest;
}

char * strcat (char * dest, char * src) {
	char * p = dest;
	while (*p)
		p++;
	while (*src) 
		*p++ = *src++;
	*p = *src;
	return dest;
}

int strcmp (char * str1, char * str2) {
	while (*str1 && *str2)
		if (*str1++ != *str2++)
			return 0;
	return *str1 == *str2;
}

size_t strlen (char * str) {
	char * p = str;
	while (*p) { p++; }
	return p - str;
}
