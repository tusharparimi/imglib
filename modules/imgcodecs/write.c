#include "write.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void WriteImage(Image *image, const char *filepath) {

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

    if (strcmp(file_extension, "pbm") == 0) {
        // default: format = P4 (Use WritePxm directly for other format, no max_value needed so given -1)
        WritePxm(image, filepath, "P4", -1);
    }
    else if (strcmp(file_extension, "pgm") == 0) {
        // default: format = P5, max_value = 255 (Use WritePxm directly for other format and max_value)
        WritePxm(image, filepath, "P5", 255); 
    }
    else if (strcmp(file_extension, "ppm") == 0) {
        // default: format = P6, max_value = 255 (Use WritePxm directly for other format and max_value)
        WritePxm(image, filepath, "P6", 255);
    }

}