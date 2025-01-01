#ifndef WIND_H
#define WIND_H

#include "core.h"
#include <windows.h>

int InitializeWindow(int width, int height);
void CleanupWindow();
void DrawPixel(int x, int y, COLORREF color);
int ProcessMessages();

#endif