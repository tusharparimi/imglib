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

unsigned char *binary2pixelData(int width, int height, unsigned char *bytes) {
    int w = width;
    int h = height;
    int bytes_per_row = (width + 7) / 8;
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int byte_index = y * bytes_per_row + x/8;
            int bit_index = x % 8;
            unsigned char byte = bytes[byte_index];
            // printf("%d %d\n", byte_index, bit_index);

            unsigned char pixel = (byte >> (7 - bit_index)) & 1;
            // printf("%u\n", pixel);

            pixelData[((y * width) + x) * 3 + 0] = pixel * 255;
            pixelData[((y * width) + x) * 3 + 1] = pixel * 255;
            pixelData[((y * width) + x) * 3 + 2] = pixel * 255;

        }
    }

    printf("%d, %d, %d, %d, %d\n", width, height, bytes_per_row, bytes_per_row*height, 8-(width % 8));

    return pixelData;
}