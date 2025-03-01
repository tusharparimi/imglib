#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    // const char *filename = 
    // "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pbm\\letter_a.pbm";

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pbm\\washington.pbm";

    // const char *filename = 
    // "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pbm\\sierpinski.pbm";

    Image *image;
    image = ReadImage(filename);

    if (image == NULL){
        printf("Error\n");
        exit(1);
    }

    printf("width: %d, height: %d\n", image->width, image->height);

    DisplayImage(image, L"First image");
    WaitKey(0);

    return 0;
}