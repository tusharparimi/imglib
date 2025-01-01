#include "wind.h"
#include <stdint.h>

// Library Interface
static HWND hwnd = NULL;
static HDC hdc = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int InitializeWindow(int width, int height) {
    const char CLASS_NAME[] = "PixelWindowClass";

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        return 0;
    }

    hwnd = CreateWindowEx(
        0,                            // Optional window styles
        CLASS_NAME,                   // Window class
        "Pixel Window",              // Window text
        WS_OVERLAPPEDWINDOW,          // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, // Size and position
        NULL,                         // Parent window
        NULL,                         // Menu
        hInstance,                    // Instance handle
        NULL                          // Additional application data
    );

    if (!hwnd) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
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
    UnregisterClass("PixelWindowClass", GetModuleHandle(NULL));
}

void DrawPixel(int x, int y, COLORREF color) {
    if (hdc) {
        SetPixel(hdc, x, y, color);
    }
}

int ProcessMessages() {
    MSG msg = {0};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            return 0;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 1;
}

// Example of usage (can be moved to a test program)
/*
int main() {
    if (!InitializeWindow(800, 600)) {
        return 0;
    }

    for (int x = 100; x < 200; x++) {
        for (int y = 100; y < 200; y++) {
            DrawPixel(x, y, RGB(255, 0, 0)); // Red color
        }
    }

    while (ProcessMessages()) {
        // Keep the window running
    }

    CleanupWindow();
    return 0;
}
*/



