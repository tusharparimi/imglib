#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *decode_pbm_P1_data(FILE *fptr, int width, int height) {
    unsigned char *data = (unsigned char *)malloc(width * height);
    if (data == NULL){
        fclose(fptr);
        printf("Failed to allocate memory for image data\n");
        return NULL;
    }

    unsigned char c;
    int i = 0;
    while((c = fgetc(fptr)) != EOF && i < (width * height)){
    // while((c = fgetc(fptr)) != EOF){
        if (c == '\n' || c == ' ' || c == '\r'){
            // if (c == '\n') {printf("char: newline\n");}
            // if (c == '\r') {printf("char: carraige\n");}
            // if (c == ' ') {printf("char: space\n");}
            continue;
        }
        // printf("char: %c ", c);
        *(data + i) = c - '0';
        i++;
        // printf("%d\n", i);    
    }
    printf("\n");

    unsigned char *pixelData = ascii2pixelData(width, height, data);
    free(data);

    return pixelData;
}


Image *read_pbm(const char *filename){
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL){
        printf("Error opening file\n");
        return NULL;
    }

    char format[3];
    if (fscanf(fptr, "%2s", format) != 1 || (strcmp(format, "P1") != 0 && strcmp(format, "P4") != 0)) {
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

    int pixel_count = width * height;
    fgetc(fptr);
    unsigned char *pixelData;

    if (strcmp(format, "P1") == 0) {
        pixelData = decode_pbm_P1_data(fptr, width, height);
    }

    else if (strcmp(format, "P4") == 0) {
        printf("read for P4 format Not Implemented\n");
        fclose(fptr);
        return NULL;
    }
    
    fclose(fptr);

    Image *image = (Image *)malloc(sizeof(Image));
    if (image == NULL){
        free(pixelData);
        printf("Failed to allocate memory for image structure\n");
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->data = pixelData;
    return image;

}



