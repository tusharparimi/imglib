#include "write_pxm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void EncodeData_P1(FILE *fptr, int width, int height, unsigned char *data) {
    
    unsigned char ascii_value;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            ascii_value = data[((y * width) + x) * 3] == 255 ? 0 : 1;
            fprintf(fptr, "%hu ", ascii_value);
        }
        fprintf(fptr, "%c", '\n');
    } 
}

void EncodeData_P2(FILE *fptr, int width, int height, unsigned char *data, unsigned char max_value) {

    unsigned char ascii_value;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) { 
            
            ascii_value = (data[((y * width) + x) * 3] * max_value) / 255;
            fprintf(fptr, "%hu ", ascii_value);
        }
        fprintf(fptr, "%c", '\n');
    }
}

void EncodeData_P3(FILE *fptr, int width, int height, unsigned char *data, unsigned char max_value) {

    unsigned char ascii_r;
    unsigned char ascii_g;
    unsigned char ascii_b;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (max_value == 255) {
                ascii_b = data[((y * width) + x) * 3 + 0];
                ascii_g = data[((y * width) + x) * 3 + 1];
                ascii_r = data[((y * width) + x) * 3 + 2];
            }
            else {
                ascii_b = (data[((y * width) + x) * 3 + 0] * max_value) / 255;
                ascii_g = (data[((y * width) + x) * 3 + 1] * max_value) / 255;
                ascii_r = (data[((y * width) + x) * 3 + 2] * max_value) / 255;
            }
            
            fprintf(fptr, "%hu %hu %hu ", ascii_r, ascii_g, ascii_b);
        }
        fprintf(fptr, "%c", '\n');
    }
}

void EncodeData_P4(FILE *fptr, int width, int height, unsigned char *data) {

    int bytes_per_row = (width + 7) / 8;
    int num_padded_bits = (width % 8 == 0) ? 0 : 8 - (width % 8);
    
    unsigned char *total_bits_with_padded = (unsigned char *)malloc(sizeof(unsigned char) * bytes_per_row * height * 8);
    if (total_bits_with_padded == NULL) {
        free(total_bits_with_padded);
        printf("Memory not allocated.\n");
        exit(1);
    }

    unsigned char byte = 0;
    int i = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            int bit_value = (data[((y * width) + x) * 3] == 255) ? 0 : 1;
            total_bits_with_padded[i++] = bit_value;
        }
        for (int p = 0; p < num_padded_bits; p++) {
            total_bits_with_padded[i++] = 0;
        }
    }

    printf("total_bits: %d, bytes_per_row: %d, num_padded_bits: %d\n", i, bytes_per_row, num_padded_bits);

    unsigned char *total_bytes = (unsigned char *)malloc(sizeof(unsigned char) * bytes_per_row * height);
    if (total_bytes == NULL) {
        free(total_bytes);
        printf("Memory not allocated.\n");
        exit(1);
    }

    for (int i = 0; i < bytes_per_row*height; i++) {
        unsigned char bit = 0;
        unsigned char byte = 0;
        
        for (int j = 0; j < 8; j++) {
            bit = total_bits_with_padded[(i * 8) + j];
            byte = (byte << 1) | bit;
        }
        total_bytes[i] = byte;
    }

    fwrite(total_bytes, sizeof(unsigned char), bytes_per_row * height, fptr);
    free(total_bits_with_padded);
    free(total_bytes);
}

void EncodeData_P5(FILE *fptr, int width, int height, unsigned char *data, unsigned char max_value) {

    unsigned char byte_value;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            byte_value = (data[((y * width) + x) * 3] * max_value) / 255;
            fwrite(&byte_value, sizeof(unsigned char), 1, fptr);
        }
    }
}

void EncodeData_P6(FILE *fptr, int width, int height, unsigned char *data, unsigned char max_value) {
    
    unsigned char byte_r;
    unsigned char byte_g;
    unsigned char byte_b;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (max_value == 255) {
                byte_b = data[((y * width) + x) * 3 + 0];
                byte_g = data[((y * width) + x) * 3 + 1];
                byte_r = data[((y * width) + x) * 3 + 2];
            }
            else {
                byte_b = (data[((y * width) + x) * 3 + 0] * max_value) / 255;
                byte_g = (data[((y * width) + x) * 3 + 1] * max_value) / 255;
                byte_r = (data[((y * width) + x) * 3 + 2] * max_value) / 255;
            }

            fwrite(&byte_r, sizeof(unsigned char), 1, fptr);
            fwrite(&byte_g, sizeof(unsigned char), 1, fptr);
            fwrite(&byte_b, sizeof(unsigned char), 1, fptr);
        }
    }
}


void WritePxm(Image *image, const char *filepath, const char* format, unsigned char max_value) {

    FILE *fptr;
    if (strcmp(format, "P1") == 0 || strcmp(format, "P2") == 0 || strcmp(format, "P3") == 0) {
        fptr = fopen(filepath, "w");
        if (fptr == NULL) {
            printf("Error opening file\n");
            exit(1);
        }
    }
    else {
        fptr = fopen(filepath, "wb");
        if (fptr == NULL) {
            printf("Error opening file\n");
            exit(1);
        }
    }

    fprintf(fptr, "%s\n", format);
    fprintf(fptr, "%d %d\n", image->width, image->height);

    if (strcmp(format, "P2") == 0 || strcmp(format, "P3") == 0 || 
    strcmp(format, "P5") == 0 || strcmp(format, "P6") == 0) {
        fprintf(fptr, "%d\n", max_value);    
    }

    if (strcmp(format, "P1") == 0) {
        EncodeData_P1(fptr, image->width, image->height, image->data);
    }
    else if (strcmp(format, "P2") == 0) {
        EncodeData_P2(fptr, image->width, image->height, image->data, max_value);
    }
    else if (strcmp(format, "P3") == 0) {
        EncodeData_P3(fptr, image->width, image->height, image->data, max_value);
    }
    else if (strcmp(format, "P4") == 0) {
        EncodeData_P4(fptr, image->width, image->height, image->data);
    }
    else if (strcmp(format, "P5") == 0) {
        EncodeData_P5(fptr, image->width, image->height, image->data, max_value);
    }
    else {
        EncodeData_P6(fptr, image->width, image->height, image->data, max_value);
    }

    fclose(fptr);
}