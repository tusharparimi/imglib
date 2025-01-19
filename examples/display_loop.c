/* 
Epilepsy Warning: 
Careful if you are photosensitive, flashing lights ahead. :)
*/

#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main(int argc, char *argv[]) {

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pbm\\enlarged_j_ascii.pbm";

    Image *image;
    image = read_pxm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image->width, image->height);

    const char *filename1 = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\pbm\\enlarged_a_ascii.pbm";

    Image *image1;
    image1 = read_pxm(filename1);

    if (image1 == NULL){
        printf("Error\n");
    }

    printf("width: %d, height: %d\n", image1->width, image1->height);

    Image *img = image;
    for (int i = 0; i < 3000; i++) {
        if (i % 2 == 0) {
            img = image1;
        }
        else {
            img = image;
        }
        DisplayImage(img, L"First image");
        DisplayImage(img, L"Second image");
        WaitKey(1);
    }

    PrintActiveWindows();
    DestroyAllWindows();
    printf("After Cleanup...\n");
    PrintActiveWindows();

    return 0;
}