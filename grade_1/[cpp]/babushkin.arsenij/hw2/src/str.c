#include "str.h"

char * strcpy (char * dest, const char * src) {
	char * p = dest;
	while (*src) 
		*p++ = *src++;
	*p = *src;
	return dest;
}

char * strcat (char * dest, const char * src) {
	char * p = dest;
	while (*p)
		p++;
	while (*src) 
		*p++ = *src++;
	*p = *src;
	return dest;
}

int strcmp (const char * str1, const char * str2) {
	while (*str1 && *str1 == *str2)
		str1++, str2++;
	return *str1 - *str2;
}

size_t strlen (const char * str) {
	const char * p = str;
	while (*p) { p++; }
	return p - str;
}
