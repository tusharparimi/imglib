// Example of usage (can be moved to a test program)
#include "highgui.h"
#include "imgcodecs.h"
#include <stdio.h>


int main() {

    const char *filename = 
    "C:\\Users\\tusha\\Documents\\projects\\imglib\\images\\enlarged_j_ascii.pbm";

    Image *image;
    image = read_pbm(filename);

    if (image == NULL){
        printf("Error\n");
    }

    unsigned char *pixelData = img2pixelData(image);
    if (pixelData == NULL) {
        exit(0);
    }


    if (!InitializeWindow(image->width, image->height)) {
        return 0;
    }

    int w, h;
    w = image->width;
    h = image->height;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char R, G, B;
            B = pixelData[((y * w) + x) * 3 + 0];
            G = pixelData[((y * w) + x) * 3 + 1];
            R = pixelData[((y * w) + x) * 3 + 2];
            // printf("[%u %u %u], ", B, G, R);
            DrawPixel(x, y, RGB(R, G, B)); // Red color
        }
        // printf("\n");
    }

    while (ProcessMessages()) {
        // Keep the window running
    }

    CleanupWindow();
    return 0;
}
