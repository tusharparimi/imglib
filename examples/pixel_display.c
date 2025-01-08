#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\enlarged_j_ascii.pbm";

    Image *image;
    image = read_pbm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image->width, image->height);

    const char *filename1 = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\enlarged_a_ascii.pbm";

    Image *image1;
    image1 = read_pbm(filename1);

    if (image1 == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image1->width, image1->height);

    DisplayImage(image, L"First image");
    WaitKey(8000);

    DisplayImage(image1, L"Second image");
    WaitKey(8000);

    return 0;
}