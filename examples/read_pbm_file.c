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
    for (int i = 0; i < image->width * image->height * 3; i++) {
        if (i % (image->width * 3) == 0) {
            printf("\n");
        }
        printf("%3u ", *(image->data + i));
    }

    free(image);

    const char *filename1 = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\letter_a.pbm";
    printf("%s\n", filename1); 

    Image *image1;
    image1 = read_pbm(filename1);

    if (image1 == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d", image1->width, image1->height);
    printf("\ndata:\n");
    for (int i = 0; i < image1->width * image1->height * 3; i++) {
        if (i % (image1->width * 3) == 0) {
            printf("\n");
        }
        printf("%3u ", *(image1->data + i));
    }

    free(image1);

    return 0;
}