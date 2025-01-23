#ifndef WINDOW_H
#define WINDOW_H

#define UNICODE
#define _UNICODE

#include "core.h"
#include <windows.h>

typedef struct {
    wchar_t *winname; // window name
    HWND hwnd;        // window handle
    HDC hdc;          // device context handle
} DisplayHandle;

int DisplayImage(Image *image, wchar_t *windowName);
int WaitKey(int delay);
void CleanupWindow(HWND hwnd);
void DestroyAllWindows();
void PrintActiveWindows();

#endif