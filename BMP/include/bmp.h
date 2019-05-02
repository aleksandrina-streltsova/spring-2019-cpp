#pragma once
#include <stdint.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)

typedef struct BITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct PIXEL {
    uint8_t rgb[3];
} PIXEL;

typedef struct BITMAP {
    BITMAPFILEHEADER biFileHeader;
    BITMAPINFOHEADER biInfoHeader;
    PIXEL *biBuffer;
} BITMAP;

int load_bmp(const char *filename, BITMAP *b);
int save_bmp(const char *filename, BITMAP *b);
int crop(BITMAP *b, BITMAP *new_image, LONG x, LONG y, LONG w, LONG h);
void rotate(BITMAP *b);