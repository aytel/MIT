#ifndef BMP
#define BMP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint16_t WORD, *PWORD, *LPWORD;
typedef uint32_t DWORD, *PDWORD, *LPDWORD;
typedef int32_t LONG, *PLONG, *LPLONG;

#define swap(x, y) do { \
	__typeof(x) temp = x; \
	x = y; \
	y = temp; \
} while (0)

#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER {
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBMPIMAGE {
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned char **data;
} BMPIMAGE, *PBMPIMAGE;

#pragma pack(pop)

int load_bmp(PBMPIMAGE pic, FILE * file);
void save_bmp(PBMPIMAGE pic, FILE * file);
void delete_bmp(PBMPIMAGE pic);
int crop_bmp(PBMPIMAGE dest, PBMPIMAGE src, int l, int r, int d, int u);
int turn_bmp(PBMPIMAGE dest, PBMPIMAGE src);

#endif