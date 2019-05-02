#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

const WORD byteCount = 3, padding = 4;

int load_bmp(const char *filename, BITMAP *b) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
        return 1;
    fread(&(b->biFileHeader), sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&(b->biInfoHeader), sizeof(BITMAPINFOHEADER), 1, fp);
    LONG width = b->biInfoHeader.biWidth, height = b->biInfoHeader.biHeight;
    LONG i, sign = 1, top = 0;
    b->biFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    if (height < 0) {
        b->biInfoHeader.biHeight = -height;
        height *= -1;
        sign = -1;
        top = height - 1;
    }
    LONG residue = width % padding;
    b->biBuffer = malloc(sizeof(PIXEL) * height * width);
    if (b->biBuffer == NULL)
        return 2;
    fseek(fp, b->biFileHeader.bfOffBits, 0);
    for (i = 0; i < height; i++) {
        fread(b->biBuffer + width * (top + sign * i), sizeof(PIXEL), width, fp);
        fseek(fp, residue, 1);
    }
}

int save_bmp(const char *filename, BITMAP *b) {
    FILE *fout = fopen(filename, "w");
    if (fout == NULL)
        return 1;
    fwrite(&(b->biFileHeader), sizeof(BITMAPFILEHEADER), 1, fout);
    fwrite(&(b->biInfoHeader), sizeof(BITMAPINFOHEADER), 1, fout);
    LONG width = b->biInfoHeader.biWidth, height = b->biInfoHeader.biHeight, i, j;
    uint8_t empty = 0;
    LONG residue = width % padding;
    for (i = 0; i < height; i++) {
        fwrite(b->biBuffer + width * i, sizeof(PIXEL), width, fout);
        for (j = 0; j < residue; j++) {
            fwrite(&empty, sizeof(uint8_t), 1, fout);
        }
    }
}

int crop(BITMAP *b, BITMAP *new_image, LONG x, LONG y, LONG w, LONG h) {
    LONG width = b->biInfoHeader.biWidth, height = b->biInfoHeader.biHeight;
    if (!(0 < w && 0 < h && 0 <= x && x + w <= width && 0 <= y && y + h <= height))
        return 3;
    new_image->biFileHeader = b->biFileHeader;
    new_image->biInfoHeader.biSizeImage = (byteCount * w + w % padding) * h;
    new_image->biFileHeader.bfSize = new_image->biFileHeader.bfOffBits + new_image->biInfoHeader.biSizeImage;
    new_image->biInfoHeader = b->biInfoHeader;
    new_image->biInfoHeader.biHeight = h;
    new_image->biInfoHeader.biWidth = w;
    new_image->biBuffer = malloc(sizeof(PIXEL) * w * h);
    LONG i, j, k;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            for (k = 0; k < byteCount; k++) {
                (new_image->biBuffer + i * w + j)->rgb[k] = (b->biBuffer + (height - (y + h) + i) * width + x + j)->rgb[k];
            }
        }
    }
}

void rotate(BITMAP *b) {
    LONG width = b->biInfoHeader.biWidth, height = b->biInfoHeader.biHeight, XPerMeter = b->biInfoHeader.biXPelsPerMeter;
    PIXEL *buffer = malloc(sizeof(PIXEL) * width * height);
    LONG i, j, k;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            for (k = 0; k < byteCount; k++) {
                buffer[i * height + j].rgb[k] = (b->biBuffer + j * width + width - 1 - i)->rgb[k];
            }
        }
    }
    for (i = 0; i < width * height; i++) {
        for (k = 0; k < byteCount; k++) {
            (b->biBuffer + i)->rgb[k] = buffer[i].rgb[k];
        }
    }
    free(buffer);
    b->biInfoHeader.biWidth = height;
    b->biInfoHeader.biHeight = width;
    b->biInfoHeader.biSizeImage = (byteCount * height + height % padding) * width;
    b->biFileHeader.bfSize = b->biFileHeader.bfOffBits + b->biInfoHeader.biSizeImage;
    b->biInfoHeader.biXPelsPerMeter = b->biInfoHeader.biYPelsPerMeter;
    b->biInfoHeader.biYPelsPerMeter = XPerMeter;
}