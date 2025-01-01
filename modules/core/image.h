#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

unsigned char *img2pixelData(Image *image);

#endif