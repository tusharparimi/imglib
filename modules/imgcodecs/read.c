#include "read.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int GetExtensionIndexfromfilepath(const char *filepath) {
    int i = (int)strlen(filepath) - 1;
    while (i > 0) {
        if (filepath[i] == '.') {
            return i + 1;
        }
        i--;
    }

    return -1;
}


Image *ReadImage(const char *filepath) {

    int extension_idx = GetExtensionIndexfromfilepath(filepath);
    assert((extension_idx > 0 && extension_idx < strlen(filepath)) && "Error in file extension format");

    char *file_extension = (char *)malloc((strlen(filepath) - extension_idx) * sizeof(char));
    for (int i = extension_idx; i < strlen(filepath); i++) {
        *(file_extension + (i - extension_idx)) = filepath[i];
        i++;
    }

    if (strcmp(file_extension, "pbm") || strcmp(file_extension, "pgm") || strcmp(file_extension, "ppm")) {
        Image *image = ReadPxm(filepath);
        return image;
    }

    return NULL;
}