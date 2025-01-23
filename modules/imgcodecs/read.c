#include "read.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int GetExtensionIndexfromFilename(const char *filename) {
    int i = (int)strlen(filename) - 1;
    while (i > 0) {
        if (filename[i] == '.') {
            return i + 1;
        }
        i--;
    }

    return -1;
}


Image *ReadImage(const char *filename) {

    int extension_idx = GetExtensionIndexfromFilename(filename);
    assert((extension_idx > 0 && extension_idx < strlen(filename)) && "Error in file extension format");

    char *file_extension = (char *)malloc((strlen(filename) - extension_idx) * sizeof(char));
    for (int i = extension_idx; i < strlen(filename); i++) {
        *(file_extension + (i - extension_idx)) = filename[i];
        i++;
    }

    if (strcmp(file_extension, "pbm") || strcmp(file_extension, "pgm") || strcmp(file_extension, "ppm")) {
        Image *image = ReadPxm(filename);
        return image;
    }

    return NULL;
}