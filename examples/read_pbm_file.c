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
        if (i % 18 == 0) {
            printf("\n");
        }
        printf("%3u ", *(image->data + i));
    }

    free(image);

    return 0;
}