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
            // printf("%u ", (data[(y * w) + x] * 255)/max_value);

            pixelData[((y * w) + x) * 3 + 0] = r;
            pixelData[((y * w) + x) * 3 + 1] = g;
            pixelData[((y * w) + x) * 3 + 2] = b;

            // printf("%u ", (pixelData[(y * w) + x]));
        }
    }
    // printf("\n");

    return pixelData;
}

unsigned char *binary2pixelData(int width, int height, unsigned char *bytes) {
    int w = width;
    int h = height;
    int bytes_per_row = (w + 7) / 8;
    int last_byte_num_pixels = (w % 8);
    unsigned char *pixelData = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    if (pixelData == NULL) {
        free(pixelData);
        printf("Memory not allocated.\n");
        return NULL;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

            // printf("y: %d x: %d\n", y, x);

            int byte_index = y * bytes_per_row + (x / 8);
            int bit_index = x % 8;
            // printf("byte_index: %d bit_index: %d\n", byte_index, bit_index);
            
            unsigned char byte = bytes[byte_index];
            // printf("byte: %c\n", byte);

            unsigned char pixel = (byte >> (7 - bit_index)) & 1;
            // printf("pixel: %d\n", pixel);

            // printf("r: %d\n", ((y * w) + x) * 3 + 0);
            // printf("g: %d\n", ((y * w) + x) * 3 + 1);
            // printf("b: %d\n", ((y * w) + x) * 3 + 2);
            //ternary operator used to reverse 0s and 1s, in pbm  0 is white and 1 is black
            pixelData[((y * w) + x) * 3 + 0] = (pixel == 0 ? 1 : 0) * 255;
            pixelData[((y * w) + x) * 3 + 1] = (pixel == 0 ? 1 : 0) * 255;
            pixelData[((y * w) + x) * 3 + 2] = (pixel == 0 ? 1 : 0) * 255;

        }
        // printf("break\n\n\n");
    }

    printf("%d, %d, %d, %d, %d, %d, %d\n", width, height, width*height, bytes_per_row, 
    bytes_per_row*height, 8-(width % 8), w*h*3);

    return pixelData;
}