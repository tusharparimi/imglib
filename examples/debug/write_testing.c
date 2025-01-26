#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\ppm\\sample.ppm";

    Image *image;
    image = ReadImage(filename);
    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image->width, image->height);

    const char *filename1 = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\ppm\\sample_test.ppm";


    // WritePxm(image, filename1, "P6", 255);
    WriteImage(image, filename1);

    Image *image1;
    image1 = ReadImage(filename1);
    if (image1 == NULL) {
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image1->width, image1->height);

    DisplayImage(image, L"Original Image");
    DisplayImage(image1, L"New Written Image");
    WaitKey(0);

    return 0;
}