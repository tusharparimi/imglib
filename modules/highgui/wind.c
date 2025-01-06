#include "wind.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_WINDOWS 1

// Library Interface
static HWND hwnd = NULL;
static HDC hdc = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Retrieve ImageData pointer
        Image *image = (Image *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        // printf("%d %d\n", image->width, image->height);
        unsigned char *pixelData = img2pixelData(image);

        if (image && pixelData) {
            BITMAPINFO bmi = { 0 };
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = image->width;
            bmi.bmiHeader.biHeight = -image->height; // Negative to flip vertically
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 24;
            bmi.bmiHeader.biCompression = BI_RGB;

            StretchDIBits(hdc,
                0, 0, image->width, image->height,   // Destination
                0, 0, image->width, image->height,   // Source
                pixelData, &bmi, DIB_RGB_COLORS, SRCCOPY);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    default: {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
}

int DisplayImage(Image *image, wchar_t *windowName) {
    
    const wchar_t CLASS_NAME[] = L"PixelWindowClass";

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        return 0;
    }

    hwnd = CreateWindowExW(
        0,                            // Optional window styles
        CLASS_NAME,                   // Window class
        windowName,              // Window text
        WS_OVERLAPPEDWINDOW,          // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, image->width, image->height, // Size and position
        NULL,                         // Parent window
        NULL,                         // Menu
        hInstance,                    // Instance handle
        NULL                          // Additional application data
    );

    if (!hwnd) {
        return 0;
    }

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)image);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    hdc = GetDC(hwnd);

    return 1;
}

void CleanupWindow() {
    if (hdc) {
        ReleaseDC(hwnd, hdc);
        hdc = NULL;
    }
    if (hwnd) {
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    UnregisterClass(L"PixelWindowClass", GetModuleHandle(NULL));
}



