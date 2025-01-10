#include "image.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char *img2pixelData(Image *image) {
    int w = image->width;
    int h = image->height;
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) { 
            pixelData[((y * w) + x) * 3 + 0] = image->data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 1] = image->data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 2] = image->data[(y * w) + x] * 255;
        }
    }

    return pixelData;
}