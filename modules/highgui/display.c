#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

// extern unsigned char *pixelData;

// static bool quit = false;

// static BITMAPINFO frame_bitmap_info;
// static HBITMAP frame_bitmap = 0;
// static HDC frame_device_context = 0;


// LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
//     switch(message) {
//         case WM_QUIT:
//         case WM_DESTROY: {
//             quit = true;
//         } break;

//         case WM_PAINT: {
//             static PAINTSTRUCT paint;
//             static HDC device_context;
//             device_context = BeginPaint(window_handle, &paint);
//             BitBlt(device_context,
//                    paint.rcPaint.left, paint.rcPaint.top,
//                    paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top,
//                    frame_device_context,
//                    paint.rcPaint.left, paint.rcPaint.top,
//                    SRCCOPY);
//             EndPaint(window_handle, &paint);
//         } break;

//         case WM_SIZE: {
//             frame_bitmap_info.bmiHeader.biWidth  = LOWORD(lParam);
//             frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

//             if(frame_bitmap) DeleteObject(frame_bitmap);
//             frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
//             SelectObject(frame_device_context, frame_bitmap);

//             frame.width =  LOWORD(lParam);
//             frame.height = HIWORD(lParam);
//         } break;

//         default: {
//             return DefWindowProc(window_handle, message, wParam, lParam);
//         }
//     }
//     return 0;
// }

// void CreateImageWindow(unsigned char *pixelData) {

//     const wchar_t window_class_name[] = L"My Window Class";
//     static WNDCLASS window_class = { 0 };
//     window_class.lpfnWndProc = WindowProcessMessage;
//     window_class.hInstance = GetModuleHandle(NULL);
//     window_class.lpszClassName = window_class_name;
//     RegisterClass(&window_class);

//     frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
//     frame_bitmap_info.bmiHeader.biPlanes = 1;
//     frame_bitmap_info.bmiHeader.biBitCount = 32;
//     frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
//     frame_device_context = CreateCompatibleDC(0);

//     static HWND window_handle;
//     window_handle = CreateWindow(window_class_name, L"Drawing Pixels", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
//                                  640, 300, 640, 480, NULL, NULL, GetModuleHandle(NULL), NULL);
//     if(window_handle == NULL) { return -1; }

//     while(!quit) {
//         static MSG message = { 0 };
//         while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { DispatchMessage(&message); }

//         // static unsigned int p = 0;
//         // frame.pixels[(p++)%(frame.width*frame.height)] = Rand32();
//         // frame.pixels[Rand32()%(frame.width*frame.height)] = 0;



//         InvalidateRect(window_handle, NULL, FALSE);
//         UpdateWindow(window_handle);
//     }

//     return 0;
// }

// void display_image(Image *image) {
//     unsigned char *pixelData;
//     pixelData = img2pixelData(image);
//     createImageWindow(pixelData);
// }



// // Function to create and display a bitmap from memory
// void DisplayBitmap(HDC hdc, int width, int height, unsigned char *pixelData) {
//     // Create a BITMAPINFO structure
//     BITMAPINFO bmi;
//     ZeroMemory(&bmi, sizeof(bmi));
//     bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//     bmi.bmiHeader.biWidth = width;
//     bmi.bmiHeader.biHeight = -height; // Negative height for top-down bitmap
//     bmi.bmiHeader.biPlanes = 1;
//     bmi.bmiHeader.biBitCount = 24; // 24 bits for RGB
//     bmi.bmiHeader.biCompression = BI_RGB;

//     // Create a memory device context
//     HDC memDC = CreateCompatibleDC(hdc);

//     // Create the bitmap
//     void *dibPixels = NULL;
//     HBITMAP hBitmap = CreateDIBSection(memDC, &bmi, DIB_RGB_COLORS, &dibPixels, NULL, 0);
    
//     if (hBitmap) {
//         // Copy the pixel data to the DIB's buffer
//         memcpy(dibPixels, pixelData, width * height * 3);

//         // Select the bitmap into the device context
//         HGDIOBJ oldBitmap = SelectObject(memDC, hBitmap);

//         // BitBlt or StretchBlt to display it on the screen
//         BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

//         // Clean up
//         SelectObject(memDC, oldBitmap);
//         DeleteObject(hBitmap);
//         DeleteDC(memDC);
//     }
// }

// // Window Procedure function
// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    
//     // static unsigned char *pixelData = NULL;
//     unsigned char *pixelData = (unsigned char *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

//     switch (uMsg) {
//         // case WM_CREATE:
//         //     // Retrieve pixelData from CREATESTRUCT
//         //     CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
//         //     pixelData = (unsigned char*)pCreate->lpCreateParams;
//         //     break;

//         case WM_PAINT: {
//             PAINTSTRUCT ps;
//             HDC hdc = BeginPaint(hwnd, &ps);
//             DisplayBitmap(hdc, 100, 100, pixelData);
//             EndPaint(hwnd, &ps);
//             break;
//         }

//         case WM_DESTROY:
//             free(pixelData); // Clean up allocated memory
//             PostQuitMessage(0);
//             break;

//         default:
//             return DefWindowProc(hwnd, uMsg, wParam, lParam);
//     }
//     return 0;
// }

// void ShowImageWindow(unsigned char *pixelData) {
//     const wchar_t CLASS_NAME[] = L"Sample Window Class";

//     WNDCLASSW wc = {0};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = GetModuleHandle(NULL);
//     wc.lpszClassName = CLASS_NAME;

//     RegisterClassW(&wc);

//     HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Display Bitmap Example", WS_OVERLAPPEDWINDOW,
//                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//                                NULL, NULL, GetModuleHandle(NULL), NULL);

//     // Store the pixelData Pointer
//     SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pixelData);

//     ShowWindow(hwnd, SW_SHOW);

//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
// }


// void display_image(Image *image){
//     unsigned char *pixelData;
//     pixelData = img2pixelData(image);
//     ShowImageWindow(pixelData);
    
// }

