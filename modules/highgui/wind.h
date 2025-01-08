#ifndef WIND_H
#define WIND_H

#define UNICODE
#define _UNICODE

#include "core.h"
#include <windows.h>

int DisplayImage(Image *image, wchar_t *windowName);
int WaitKey(int delay);
void CleanupWindow();

#endif