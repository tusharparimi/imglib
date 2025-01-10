#include "wind.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int capacity = 3;
DisplayHandle *dHandles;
int numHandles = 0;
int firstHandle = 0;
const wchar_t CLASS_NAME[] = L"PixelWindowClass";
HINSTANCE hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Image *image;
    if(uMsg == WM_CREATE) {
        CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
        image = (Image *)(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)image);
    }
    else {
        image = (Image *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

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
        free(pixelData);
        return 0;
    }
    case WM_KEYDOWN: {
        InvalidateRect(hwnd, NULL, TRUE); // Force window repaint
        UpdateWindow(hwnd);              // Immediately process WM_PAINT

        return 0;
    }
    case WM_CLOSE: {
        CleanupWindow(hwnd);
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

void InitializeDisplayHandles() {
    dHandles = (DisplayHandle *)malloc(capacity * sizeof(DisplayHandle));
    if (dHandles == NULL) {
        printf("Display handles array, memory allocation fails\n");
        free(dHandles);
        exit(1);
    }

    for (int i = 0; i < capacity; i++) {
        dHandles[i].winname = NULL;
        dHandles[i].hwnd = NULL;
        dHandles[i].hdc = NULL;
    }

    hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        free(dHandles);
        exit(1);
    }
}

int DisplayImage(Image *image, wchar_t *windowName) {

    int windowPresent = 0;
    int windowIndex = -1;

    for (int i = 0; i < numHandles; i++) {
        if (dHandles[i].winname == windowName) {
            windowPresent = 1;
            windowIndex = i;
        }
    }

    if (windowPresent) {
        SetWindowLongPtr(dHandles[windowIndex].hwnd, GWLP_USERDATA, (LONG_PTR)image);
        InvalidateRect(dHandles[windowIndex].hwnd, NULL, TRUE); // Force window repaint
        UpdateWindow(dHandles[windowIndex].hwnd);              // Immediately process WM_PAINT

        return 0;
    }

    if (firstHandle == 0) {
        InitializeDisplayHandles();
        firstHandle = 1;
    }
    
    numHandles++;
    if (numHandles == capacity - 1) {
        capacity = 2 * capacity;
        DisplayHandle *temp = realloc(dHandles, capacity * sizeof(DisplayHandle));
        if (!dHandles) {
            printf("Memory realloc failed\n");
            free(dHandles);
            exit(1);
        }
        dHandles = temp;
    }

    dHandles[numHandles - 1].winname = windowName;
    dHandles[numHandles - 1].hwnd = CreateWindowExW(
        0,                            // Optional window styles
        CLASS_NAME,                   // Window class
        windowName,                   // Window text
        WS_OVERLAPPEDWINDOW,          // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, image->width, image->height, // Size and position
        NULL,                         // Parent window
        NULL,                         // Menu
        hInstance,                    // Instance handle
        image                         // Additional application data
    );

    if (!dHandles[numHandles - 1].hwnd) {
        return 1;
    }

    ShowWindow(dHandles[numHandles - 1].hwnd, SW_SHOW);
    dHandles[numHandles - 1].hdc = GetDC(dHandles[numHandles - 1].hwnd);

    // printf("capacity: %d, numHandles: %d\n", capacity, numHandles);
    // printf("id: %d, winname: %ws\n", numHandles - 1, dHandles[numHandles - 1].winname);

    return 0;
}

int AnyWindowHandle() {
    for (int i = 0; i < numHandles; i++) {
        if (dHandles[i].hwnd) {
            return 1;
        }
    }
    return 0;
}

int WaitKey(int delay) {
    MSG msg = { 0 };

    if (delay <= 0) {
        while (1) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_CLOSE || msg.message == WM_KEYDOWN) {
                    break;
                }
            }
            if (!AnyWindowHandle()) {
                break;
            }    
        }
    }
    else {
        DWORD startTime = GetTickCount();
        while (1) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_CLOSE || msg.message == WM_KEYDOWN) {
                    break;
                }
            }
            if (GetTickCount() - startTime >= (DWORD)delay) {
                return 0;
            }
            if (!AnyWindowHandle()) {
                break;
            }  
        }
    }

    return 0;
}

void CleanupWindow(HWND hwnd) {
    int i;
    for (i = 0; i < numHandles; i++) {
        if (dHandles[i].hwnd == hwnd) {
            break;
        }
    }
    if (dHandles[i].hdc) {
        ReleaseDC(dHandles[i].hwnd, dHandles[i].hdc);
        dHandles[i].hdc = NULL;
    }
    if (dHandles[i].hwnd) {
        DestroyWindow(dHandles[i].hwnd);
        dHandles[i].hwnd = NULL;
    }
}

void DestroyAllWindows() {
    for (int i = 0; i < numHandles; i++) {
        if (dHandles[i].hdc) {
            ReleaseDC(dHandles[i].hwnd, dHandles[i].hdc);
            dHandles[i].hdc = NULL;
        }
        if (dHandles[i].hwnd) {
            DestroyWindow(dHandles[i].hwnd);
            dHandles[i].hwnd = NULL;
        }
        dHandles[i].winname = NULL;
    }
    UnregisterClass(L"PixelWindowClass", GetModuleHandle(NULL));
    free(dHandles);
    firstHandle = 0;
    numHandles = 0;
}

void PrintActiveWindows() {
    printf("Active windows : ");
    for (int i = 0; i < numHandles; i++) {
        printf("%ws, ", dHandles[i].winname);
    }
    printf("\n");
}

    




