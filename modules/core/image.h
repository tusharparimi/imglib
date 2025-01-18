#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

unsigned char *ascii2pixelData(int width, int height, unsigned char *data, const char *format, 
unsigned char max_value);
unsigned char *binary2pixelData(int width, int height, unsigned char *bytes);
unsigned char *P5_bytes2pixelData(int width, int height, unsigned char *bytes, unsigned char max_value);

#endif