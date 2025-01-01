#ifndef DISPLAY_H
#define DISPLAY_H

#include "core.h"

void display_image(Image *image);
void ShowImageWindow(unsigned char *pixelData);
unsigned char *img2pixelData(Image *image);


#endif