#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image *read_pbm(const char *filename){
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL){
        printf("Error opening file\n");
        return NULL;
    }

    char format[3];
    if (fscanf(fptr, "%2s", format) != 1 || strcmp(format, "P1") != 0){
        fclose(fptr);
        printf("Unsupported file format\n");
        return NULL;
    }

    int width, height;
    if (fscanf(fptr, "%d %d", &width, &height) != 2){
        fclose(fptr);
        printf("Invalid file header\n");
        return NULL;
    }

    fgetc(fptr);

    int pixel_count = width * height;
    unsigned char *data = (unsigned char *)malloc(pixel_count);
    if (data == NULL){
        fclose(fptr);
        printf("Failed to allocate memory for image data\n");
        return NULL;
    }

    if (fread(data, sizeof(int), pixel_count, fptr) != pixel_count){
        free(data);
        fclose(fptr);
        pritnf("Failed to read image data\n");
        return NULL;
    }
    
    fclose(fptr);

    Image *image = (Image *)malloc(sizeof(Image));
    if (image == NULL){
        free(data);
        printf("Failed to allocate memory for image structure\n");
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->data = data;
    return image;

}



