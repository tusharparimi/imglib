#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *ascii2pixelData(int width, int height, unsigned char *data, const char *format, 
unsigned char max_value) {
    int w = width;
    int h = height;
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) { 

            if (strcmp(format, "P1") == 0) {
                //ternary operator used to reverse 0s and 1s, in pbm  0 is white and 1 is black
                r = (data[(y * w) + x] == 0 ? 1 : 0) * 255;
                g = (data[(y * w) + x] == 0 ? 1 : 0) * 255;
                b = (data[(y * w) + x] == 0 ? 1 : 0) * 255;
            }
            else if (strcmp(format, "P2") == 0) {
                r = (data[(y * w) + x] * 255) / max_value;
                g = (data[(y * w) + x] * 255) / max_value;
                b = (data[(y * w) + x] * 255) / max_value;
            }

            pixelData[((y * w) + x) * 3 + 0] = r;
            pixelData[((y * w) + x) * 3 + 1] = g;
            pixelData[((y * w) + x) * 3 + 2] = b;

        }
    }

    return pixelData;
}

unsigned char *binary2pixelData(int width, int height, unsigned char *bytes) {

    int bytes_per_row = (width + 7) / 8;
    unsigned char *pixelData = (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            int byte_index = y * bytes_per_row + (x / 8);
            int bit_index = x % 8;
            unsigned char byte = bytes[byte_index];
            unsigned char pixel = (byte >> (7 - bit_index)) & 1;

            //ternary operator used to reverse 0s and 1s, in pbm  0 is white and 1 is black
            pixelData[((y * width) + x) * 3 + 0] = (pixel == 0 ? 1 : 0) * 255;
            pixelData[((y * width) + x) * 3 + 1] = (pixel == 0 ? 1 : 0) * 255;
            pixelData[((y * width) + x) * 3 + 2] = (pixel == 0 ? 1 : 0) * 255;

        }
    }

    return pixelData;
}

unsigned char *P5_bytes2pixelData(int width, int height, unsigned char *bytes, unsigned char max_value) {

    unsigned char *pixelData = (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char));
    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            pixelData[((y * width) + x) * 3 + 0] = ((bytes[(y * width) + x]) * 255) / max_value;
            pixelData[((y * width) + x) * 3 + 1] = ((bytes[(y * width) + x]) * 255) / max_value;
            pixelData[((y * width) + x) * 3 + 2] = ((bytes[(y * width) + x]) * 255) / max_value;

        }
    }

    return pixelData;

}