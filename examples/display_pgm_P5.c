#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    // const char *filename = 
    // "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pgm\\buffalo.pgm";

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pgm\\buffalo.pgm";

    Image *image;
    image = read_pgm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image->width, image->height);

    DisplayImage(image, L"First image");
    WaitKey(0);

    return 0;
}