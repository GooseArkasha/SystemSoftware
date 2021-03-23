// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>



static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szWindowClassChild[] = _T("Child");
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

WNDCLASSEX wcex_child;

HINSTANCE hInst;
HBRUSH greenBrush = NULL;
HWND hColorWnd;
HWND hMainWnd;
HWND Button;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

     hMainWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hMainWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }
    ShowWindow(hMainWnd,
        nCmdShow);
    UpdateWindow(hMainWnd);

////////////////////////////////////////////////////////////////////////////////////////
    //«ј„ј“»≈//
    greenBrush = CreateSolidBrush(RGB(255, 205, 143));//начальный цвет
    
    wcex_child.cbSize = sizeof(WNDCLASSEX);
    wcex_child.style = 0;
    wcex_child.lpfnWndProc = ChildProc;
    wcex_child.cbClsExtra = 0;
    wcex_child.cbWndExtra = 0;
    wcex_child.hInstance = hInstance;
    wcex_child.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex_child.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex_child.hbrBackground = greenBrush;
    wcex_child.lpszMenuName = NULL;
    wcex_child.lpszClassName = szWindowClassChild;
    wcex_child.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex_child))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hColorWnd = CreateWindow(//ребеночек
        szWindowClassChild,
        TEXT(""),
        WS_VISIBLE | WS_CHILD,
        300,
        300,
        100,
        100,
        hMainWnd,
        (HMENU)NULL,
        NULL,
        NULL);

    if (!hColorWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }
    ShowWindow(hColorWnd,nCmdShow);
    UpdateWindow(hColorWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");

    switch (message) {
    case WM_CREATE: 
        Button = CreateWindow(
            TEXT("BUTTON"),
            TEXT("йобо нопка"),
            WS_CHILD | WS_VISIBLE,
            30,
            30,
            100,
            30,
            hWnd,
            (HMENU)100,
            hInst,
            NULL);
        break;

    case WM_COMMAND:
        if (wParam == 100) {
            DeleteObject(greenBrush);
            greenBrush = CreateSolidBrush(RGB(0, 255, 0));

            SetClassLongPtr(hColorWnd, GCL_HBRBACKGROUND, (LONG)greenBrush);
            InvalidateRect(hColorWnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}