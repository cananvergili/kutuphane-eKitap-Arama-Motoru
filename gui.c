#include "gui.h"

#ifdef _WIN32

#include <windows.h>

#define BTN_START 1000
#define BTN_INFO  1001
#define BTN_EXIT  1002

static int gui_sonuc = 0;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow(
                "STATIC",
                "Kutuphane / e-Kitap Arama Motoru",
                WS_VISIBLE | WS_CHILD,
                20, 20, 320, 20,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            CreateWindow(
                "STATIC",
                "Bu proje AVL, Trie, Quick Sort, Merge Sort,\n"
                "Binary Search, Stack, Queue (BFS), CSV ve\n"
                "skorlamali arama icerir.\n"
                "Asil islevler komut satiri (CLI) uzerindedir.",
                WS_VISIBLE | WS_CHILD,
                20, 50, 360, 60,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            CreateWindow(
                "BUTTON",
                "Projeyi Baslat",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                20, 130, 140, 30,
                hwnd,
                (HMENU)BTN_START,
                NULL,
                NULL
            );

            CreateWindow(
                "BUTTON",
                "Projeyi Acikla",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                180, 130, 140, 30,
                hwnd,
                (HMENU)BTN_INFO,
                NULL,
                NULL
            );

            CreateWindow(
                "BUTTON",
                "Cik",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                140, 170, 80, 25,
                hwnd,
                (HMENU)BTN_EXIT,
                NULL,
                NULL
            );
            break;
        }

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id == BTN_START) {
                gui_sonuc = 1;
                PostQuitMessage(0);
            } else if (id == BTN_INFO) {
                MessageBox(
                    hwnd,
                    "Bu GUI, Kutuphane / e-Kitap Arama Motoru projesinin\n"
                    "gorsel tanitimi icin hazirlanmistir.\n\n"
                    "- AVL agaci ile ID arama\n"
                    "- Trie ile baslik arama\n"
                    "- Quick Sort / Merge Sort ile siralama\n"
                    "- Binary Search\n"
                    "- Stack ile arama gecmisi / undo\n"
                    "- Queue + BFS ile raflar arasinda en kisa yol\n"
                    "- CSV ile girdi/cikti\n"
                    "tum bu islevler CLI menusu uzerinden kullanilir.",
                    "Proje Ozeti",
                    MB_OK | MB_ICONINFORMATION
                );
            } else if (id == BTN_EXIT) {
                gui_sonuc = 0;      // cikis
                PostQuitMessage(0);
            }
            break;
        }

        case WM_CLOSE:
            gui_sonuc = 0;
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int gui_calistir(void) {
    const char g_szClassName[] = "KutuphaneGUIClass";

    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    gui_sonuc = 0;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Pencere sinifi kaydedilemedi!", "Hata",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        g_szClassName,
        "Kutuphane GUI - Gorsel Arayuz",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 440, 260,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Pencere olusturulamadi!", "Hata",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }


    return gui_sonuc;
}

#else

#include <stdio.h>

int gui_calistir(void) {
    printf("GUI yalnizca Windows uzerinde gosterilir.\n");
    // Linux'ta direkt CLI'yi baslatmak icin 1 donduruyoruz
    return 1;
}

#endif
