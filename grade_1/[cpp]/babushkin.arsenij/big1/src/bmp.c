#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"

int load_bmp(PBMPIMAGE pic, FILE * file) {
	fread(&pic->bfh, sizeof(pic->bfh), 1, file);
	fread(&pic->bih, sizeof(pic->bih), 1, file);

	size_t PIXEL_SIZE = pic->bih.biBitCount / 8;

	int hor = ((pic->bih.biWidth - 1) / 4 + 1) * 4;
	int ver = pic->bih.biHeight;
	if (!(pic->data = (unsigned char **)malloc(ver * sizeof(unsigned char *))))
		return 1;
	for (int i = 0; i < ver; i++) {
		if (!(pic->data[i] = (unsigned char *)calloc(hor, PIXEL_SIZE)))
			return 1;
		fread(pic->data[i], PIXEL_SIZE, hor, file);
	}
	return 0;
}

void save_bmp(PBMPIMAGE pic, FILE * file) {
	size_t PIXEL_SIZE = pic->bih.biBitCount / 8;

	fwrite(&pic->bfh, sizeof(pic->bfh), 1, file);
	fwrite(&pic->bih, sizeof(pic->bih), 1, file);
	int hor = ((pic->bih.biWidth - 1) / 4 + 1) * 4;
	int ver = pic->bih.biHeight;
	for (int i = 0; i < ver; i++)
		fwrite(pic->data[i], PIXEL_SIZE, hor, file);
	return;
}

int crop_bmp(PBMPIMAGE dest, PBMPIMAGE src, LONG l, LONG r, LONG d, LONG u) {
	size_t PIXEL_SIZE = src->bih.biBitCount / 8;

	if (l >= r || d >= u || u > src->bih.biHeight || r > src->bih.biWidth)
		return 2;

	d = src->bih.biHeight - d;
	u = src->bih.biHeight - u;
	swap(d, u);

	memcpy(&dest->bfh, &src->bfh, sizeof(src->bfh));
	memcpy(&dest->bih, &src->bih, sizeof(src->bih));
	dest->bih.biHeight = u - d;
	dest->bih.biWidth = r - l;
	int hor = ((dest->bih.biWidth - 1) / 4 + 1) * 4;
	int ver = dest->bih.biHeight;
	if (!(dest->data = (unsigned char **)malloc(ver * sizeof(unsigned char *))))
		return 1;
	for (int i = 0; i < ver; i++) {
		if (!(dest->data[i] = (unsigned char *)calloc(hor, PIXEL_SIZE)))
			return 1;
		memcpy(dest->data[i], src->data[i + d] + PIXEL_SIZE * l, PIXEL_SIZE * hor);
	}
	return 0;
}

int turn_bmp(PBMPIMAGE dest, PBMPIMAGE src) {
	size_t PIXEL_SIZE = src->bih.biBitCount / 8;

	memcpy(&dest->bfh, &src->bfh, sizeof(src->bfh));
	memcpy(&dest->bih, &src->bih, sizeof(src->bih));
	dest->bih.biHeight = src->bih.biWidth;
	dest->bih.biWidth = src->bih.biHeight;
	int hor = ((dest->bih.biWidth - 1) / 4 + 1) * 4;
	int ver = dest->bih.biHeight;
	if (!(dest->data = (unsigned char **)malloc(ver * sizeof(unsigned char *))))
		return 1;
	for (int i = 0; i < ver; i++)
		if (!(dest->data[i] = (unsigned char *)calloc(hor, PIXEL_SIZE)))
			return 1;
	for (int i = 0; i < dest->bih.biHeight; i++) {
		for (int j = 0; j < dest->bih.biWidth; j++) {
			unsigned char *to = dest->data[i] + PIXEL_SIZE * j;
			unsigned char *from = src->data[j] + PIXEL_SIZE * i;
			memcpy(to, from, PIXEL_SIZE);
		}
	}
	for (int i = 0; i < dest->bih.biHeight / 2; i++)
		swap(dest->data[i], dest->data[dest->bih.biHeight - i - 1]);
	return 0;
}

void delete_bmp(PBMPIMAGE pic) {
	int ver = pic->bih.biHeight;
	for (int i = 0; i < ver; i++) {
		free(pic->data[i]);
	}
	free(pic->data);
	return;
}