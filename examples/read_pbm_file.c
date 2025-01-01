#include "imgcodecs.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\j.pbm";
    printf("%s\n", filename); 

    Image *image;
    image = read_pbm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d", image->width, image->height);
    printf("\ndata:\n");
    for (int i = 0; i < image->width * image->height; i++){
        printf("%u ", *(image->data + i));
    }

    unsigned char *pixelData = img2pixelData(image);
    if (pixelData == NULL) {
        exit(0);
    }

    printf("\npixelated data:\n");
    for (int i = 0; i < image->width * image->height * 3; i++){
        printf("%u ", *(pixelData + i));
    }

    free(pixelData);

    return 0;
}