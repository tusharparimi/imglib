#include "imgcodecs.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\ppm\\colors_ascii1.ppm";
    printf("%s\n", filename); 

    Image *image;
    image = ReadPxm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d", image->width, image->height);
    printf("\ndata:\n");
    for (int i = 0; i < image->width * image->height * 3; i++) {
        if (i % (image->width * 3) == 0) {
            printf("\n");
        }
        printf("%3d ", *(image->data + i));
    }

    free(image);

    return 0;
}