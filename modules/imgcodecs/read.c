#include "read.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Image *ReadImage(const char *filepath) {

    int extension_idx = GetExtensionIndexfromfilepath(filepath);
    assert((extension_idx > 0 && extension_idx < strlen(filepath)) && "Error in file extension format");

    char *file_extension = (char *)malloc((strlen(filepath) - extension_idx + 1) * sizeof(char));
    if (file_extension == NULL) {
        free(file_extension);
        printf("Memory not allocated.\n");
        exit(1);
    }

    for (int i = extension_idx; i < strlen(filepath) + 1; i++) {
        if (i == strlen(filepath)) {
            *(file_extension + (i - extension_idx)) = '\0';
        }

        *(file_extension + (i - extension_idx)) = filepath[i];
    }

    if (strcmp(file_extension, "pbm") == 0 || strcmp(file_extension, "pgm") == 0 || strcmp(file_extension, "ppm") == 0) {
        Image *image = ReadPxm(filepath);
        return image;
    }

    return NULL;
}