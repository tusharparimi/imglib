#include "image.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char *img2pixelData(Image *image) {
    int w = image->width;
    int h = image->height;
    printf("Here\n");
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));
    printf("Here\n");
    if (pixelData == NULL) {
        printf("Memory not allocated.\n");
        return NULL;
    }
    printf("Here\n");

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) { 
            pixelData[((y * w) + x) * 3 + 0] = image->data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 1] = image->data[(y * w) + x] * 255;
            pixelData[((y * w) + x) * 3 + 2] = image->data[(y * w) + x] * 255;
        }
    }
    printf("%u %u %u\n", pixelData[0], pixelData[1], pixelData[2]);

    return pixelData;
}