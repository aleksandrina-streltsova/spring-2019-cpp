#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char * argv[]) {
    if (argc != 8)
        return 4;
    if (strcmp(argv[1], "crop-rotate") != 0)
        return 5;
    BITMAP bmp;
    BITMAP new_bmp;
    load_bmp(argv[2], &bmp);
    LONG x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
    crop(&bmp, &new_bmp, x, y, w, h);
    rotate(&new_bmp);
    save_bmp(argv[3], &new_bmp);
    free(new_bmp.biBuffer);
    free(bmp.biBuffer);
    return 0;
}