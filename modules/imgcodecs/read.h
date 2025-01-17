#ifndef READ_H
#define READ_H

#include "core.h"

Image *read_pbm(const char *filename);
Image *read_pgm(const char *filename);

#endif