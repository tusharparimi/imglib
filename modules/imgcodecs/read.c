#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image *read_pbm(const char *filename){
    FILE *fptr = fopen(filename, "r");
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
    printf("file_format: %s\n", format);

    int width, height;
    if (fscanf(fptr, "%d %d", &width, &height) != 2){
        fclose(fptr);
        printf("Invalid file header\n");
        return NULL;
    }

    fgetc(fptr);

    int pixel_count = width * height;
    printf("width: %d, height: %d, pixel_count: %d\n", width, height, pixel_count);
    unsigned char *data = (unsigned char *)malloc(pixel_count);
    if (data == NULL){
        fclose(fptr);
        printf("Failed to allocate memory for image data\n");
        return NULL;
    }

    // if (fread(data, sizeof(unsigned char), pixel_count, fptr) != pixel_count){
    //     free(data);
    //     fclose(fptr);
    //     printf("Failed to read image data\n");
    //     return NULL;
    // }
    unsigned char c;
    int i = 0;
    while((c = fgetc(fptr)) != EOF && i < pixel_count){
        printf("%c", c);
        if (c == '\n' || c == ' '){
            continue;
        }
        *(data + i) = c - '0';
        i++;    
    }
    // printf("\n%d\n", i);
    printf("\n");
    
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



