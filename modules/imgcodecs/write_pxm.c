#include "write_pxm.h"
#include <stdio.h>
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
    fclose(fptr); 
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
    fclose(fptr);
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
    fclose(fptr);
}

// void EncodeData_P4(FILE *fptr, int width, int height, unsigned char *data) {

//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {

//             unsigned char bit = data[((y * width) + x) * 3] == 255 ? 0 : 1;


//         }
//     }    

//     unsigned char bit
//     unsigned char byte;
// }


int WritePxm(Image *image, const char *filepath, const char* format, unsigned char max_value) {

    int ascii = 0;

    FILE *fptr = fopen(filepath, "w");
    if (fptr == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    if (strcmp(format, "P1") == 0 || strcmp(format, "P2") == 0 || strcmp(format, "P3") == 0) {
        ascii = 1;
    }

    fprintf(fptr, "%s\n", format);
    fprintf(fptr, "%d %d\n", image->width, image->height);

    if (strcmp(format, "P2") == 0 || strcmp(format, "P3") == 0 || 
    strcmp(format, "P5") == 0 || strcmp(format, "P6") == 0) {
        fprintf(fptr, "%d\n", max_value);    
    }

    if (ascii) {
        fclose(fptr);
        fptr = fopen(filepath, "ab");
        if (fptr == NULL) {
        printf("Error opening file\n");
        return -1;
        }
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

    return 0;
}