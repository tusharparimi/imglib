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

    unsigned char *pixelData = ascii2pixelData(width, height, data, "P1", 0);
    free(data);

    return pixelData;
}

unsigned char *decode_pbm_P4_data(FILE *fptr, int width, int height) {
    int bytes_per_row = (width + 7) / 8;
    unsigned char *bytes = (unsigned char *)malloc(sizeof(unsigned char) * bytes_per_row * height);
    if (bytes == NULL) {
        fclose(fptr);
        printf("Failed to allocate memory for bytes\n");
        return NULL;
    }

    if (fread(bytes, sizeof(unsigned char), bytes_per_row * height, fptr) != bytes_per_row * height) {
        fclose(fptr);
        printf("Failed to read bytes\n");
        return NULL;
    }

    unsigned char *pixelData = binary2pixelData(width, height, bytes);
    free(bytes);

    return pixelData;

}

unsigned char *decode_pgm_P2_data(FILE *fptr, int width, int height, int max_value) {
    unsigned char *data = (unsigned char *)malloc(width * height);
    if (data == NULL){
        fclose(fptr);
        printf("Failed to allocate memory for image data\n");
        return NULL;
    }

    unsigned char val;
    int c;
    int i = 0;
    while((c = fgetc(fptr)) != EOF){
        if (c == '\n' || c == ' ' || c == '\r'){
            continue;
        }
        ungetc(c, fptr);
        if (fscanf(fptr, "%hhu", &val) != 1) {
            fclose(fptr);
            printf("Error reading data from file\n");
            return NULL;
        }
        // printf("%u ", val);
        *(data + i) = val;
        i++;
    }
    // printf("\n\n");

    unsigned char *pixelData = ascii2pixelData(width, height, data, "P2", max_value);
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

    unsigned char c = fgetc(fptr);
    printf("%c", c);
    // c = fgetc(fptr);
    // printf("%c", c);
    while ((c = fgetc(fptr)) == '#' || c == ' ' || c == '\n') {
        if (c == '#' || c == ' ') {
            while (fgetc(fptr) != '\n') {}
        }
    }
    ungetc(c, fptr);

    int width, height;
    if (fscanf(fptr, "%d %d", &width, &height) != 2){
        fclose(fptr);
        printf("Invalid file header\n");
        return NULL;
    }
    printf("%d %d\n", width, height);

    int pixel_count = width * height;
    fgetc(fptr);
    // printf("Here: %d\n", fgetc(fptr));
    unsigned char *pixelData;

    if (strcmp(format, "P1") == 0) {
        pixelData = decode_pbm_P1_data(fptr, width, height);
    }

    else if (strcmp(format, "P4") == 0) {
        // printf("read for P4 format Not Implemented\n");
        // fclose(fptr);
        // return NULL;
        pixelData = decode_pbm_P4_data(fptr, width, height);
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


Image *read_pgm(const char *filename) {
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    char format[3];
    if (fscanf(fptr, "%2s", format) != 1 || (strcmp(format, "P2") != 0 && strcmp(format, "P5") != 0)) {
        fclose(fptr);
        printf("Unsupported file format\n");
        return NULL;
    }

    unsigned char c = fgetc(fptr);
    printf("%c", c);
    while ((c = fgetc(fptr)) == '#' || c == ' ' || c == '\n') {
        if (c == '#' || c == ' ') {
            while (fgetc(fptr) != '\n') {}
        }
    }
    ungetc(c, fptr);

    int width, height;
    if (fscanf(fptr, "%d %d", &width, &height) != 2){
        fclose(fptr);
        printf("Invalid file header\n");
        return NULL;
    }
    printf("%d %d\n", width, height);

    int pixel_count = width * height;
    fgetc(fptr);

    int max_value;
    if (fscanf(fptr, "%d", &max_value) != 1 || max_value < 0 || max_value > 255) {
        fclose(fptr);
        printf("Invalid max val\n");
        return NULL;
    }
    printf("%d\n", max_value);

    fgetc(fptr);

    unsigned char *pixelData;
    if (strcmp(format, "P2") == 0) {
        pixelData = decode_pgm_P2_data(fptr, width, height, max_value);
    }

    else if (strcmp(format, "P5") == 0) {
        printf("P5 format not implemented yet\n");
        fclose(fptr);
        return NULL;
        // pixelData = decode_pgm_P5_data(fptr, width, height);
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



