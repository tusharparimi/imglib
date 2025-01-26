#include "imgcodecs_utils.h"
#include <string.h>

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