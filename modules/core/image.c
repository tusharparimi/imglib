#include "image.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char *ascii2pixelData(int width, int height, unsigned char *data) {
    int w = width;
    int h = height;
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) { 
            pixelData[((y * w) + x) * 3 + 0] = data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 1] = data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 2] = data[(y * w) + x] * 255;
        }
    }

    return pixelData;
}