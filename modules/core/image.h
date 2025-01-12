#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

unsigned char *ascii2pixelData(int width, int height, unsigned char *data);
unsigned char *binary2pixelData(int width, int height, unsigned char *bytes);

#endif