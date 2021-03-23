#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


#define ID_TIMER_1 1
#define ID_TIMER_2 2
#define ID_TIMER_3 3
#define ID_TIMER_4 4
#define ID_TIMER_5 5
#define ID_TIMER_6 6
#define ID_TIMER_7 7
#define ID_TIMER_8 8


static TCHAR szMainWindowClass[] = _T("MainWindowClass");
static TCHAR szFirstChildWindowClass[] = _T("FirstChildWindowClass");
static TCHAR szSecondChildWindowClass[] = _T("SecondChildWindowClass");
static TCHAR szThirdChildWindowClass[] = _T("ThirdChildWindowClass");
static TCHAR szFourthChildWindowClass[] = _T("FourthChildWindowClass");


static TCHAR szMainWindowTitle[] = _T("MainWindow");
static TCHAR szFirstChildTitle[] = _T("First Child Window");
static TCHAR szSecondChildTitle[] = _T("Second Child Window");
static TCHAR szThirdChildTitle[] = _T("Third Child Window");
static TCHAR szFourthChildTitle[] = _T("Fourth Child Window");


HINSTANCE hInst;


UINT uFirstDeltaTime = 1000;
UINT uSecondDeltaTime = 500;

BOOL bControlFlag = false;

HWND hWndFirstChild;
HWND hWndSecondChild;
HWND hWndThirdChild;
HWND hWndFourthChild;

HBRUSH brush = NULL;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcFirstChild(HWND, UINT, WPARAM, LPARAM);


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
    wcex.lpszClassName = szMainWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szMainWindowClass,
        szMainWindowTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

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
    switch (message)
    {
    case WM_LBUTTONDOWN:
        SetTimer(hWnd, ID_TIMER_1, uFirstDeltaTime, NULL);
        break;

    case WM_TIMER:
        switch (wParam) {
        case ID_TIMER_1: {

            KillTimer(hWnd, ID_TIMER_1);

            WNDCLASSEX wcexSecondChild;

            wcexSecondChild.cbSize = sizeof(WNDCLASSEX);
            wcexSecondChild.style = CS_HREDRAW | CS_VREDRAW;
            wcexSecondChild.lpfnWndProc = WndProcFirstChild;
            wcexSecondChild.cbClsExtra = 0;
            wcexSecondChild.cbWndExtra = 0;
            wcexSecondChild.hInstance = hInst;
            wcexSecondChild.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wcexSecondChild.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcexSecondChild.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcexSecondChild.lpszMenuName = NULL;
            wcexSecondChild.lpszClassName = szSecondChildWindowClass;
            wcexSecondChild.hIconSm = LoadIcon(wcexSecondChild.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcexSecondChild))
            {
                MessageBox(NULL,
                    _T("Call to RegisterClassEx failed! (wcexSecondChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }


            hWndSecondChild = CreateWindow(
                szSecondChildWindowClass,
                szSecondChildTitle,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                300, 100,
                100, 100,
                hWnd,
                NULL,
                hInst,
                NULL
            );

            if (!hWndSecondChild)
            {
                MessageBox(NULL,
                    _T("Call to CreateWindow failed! (hWndSecondChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }

            CreateWindow(TEXT("STATIC"), TEXT("2"),
                WS_VISIBLE | WS_CHILD,
                0, 0, 20, 20,
                hWndSecondChild, (HMENU)NULL, NULL, NULL);

            SetTimer(hWnd, ID_TIMER_2, uFirstDeltaTime, NULL);

            break;
        }
        case ID_TIMER_2: {

            KillTimer(hWnd, ID_TIMER_2);

            WNDCLASSEX wcexThirdChild;

            wcexThirdChild.cbSize = sizeof(WNDCLASSEX);
            wcexThirdChild.style = CS_HREDRAW | CS_VREDRAW;
            wcexThirdChild.lpfnWndProc = WndProcFirstChild;
            wcexThirdChild.cbClsExtra = 0;
            wcexThirdChild.cbWndExtra = 0;
            wcexThirdChild.hInstance = hInst;
            wcexThirdChild.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wcexThirdChild.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcexThirdChild.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcexThirdChild.lpszMenuName = NULL;
            wcexThirdChild.lpszClassName = szThirdChildWindowClass;
            wcexThirdChild.hIconSm = LoadIcon(wcexThirdChild.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcexThirdChild))
            {
                MessageBox(NULL,
                    _T("Call to RegisterClassEx failed! (wcexThirdChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }


            hWndThirdChild = CreateWindow(
                szThirdChildWindowClass,
                szThirdChildTitle,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 300,
                100, 100,
                hWnd,
                NULL,
                hInst,
                NULL
            );

            if (!hWndThirdChild)
            {
                MessageBox(NULL,
                    _T("Call to CreateWindow failed! (hWndThirdChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }

            CreateWindow(TEXT("STATIC"), TEXT("3"),
                WS_VISIBLE | WS_CHILD,
                0, 0, 20, 20,
                hWndThirdChild, (HMENU)NULL, NULL, NULL);

            SetTimer(hWnd, ID_TIMER_3, uFirstDeltaTime, NULL);

            break;
        }
        case ID_TIMER_3: {

            KillTimer(hWnd, ID_TIMER_3);

            WNDCLASSEX wcexFirstChild;

            wcexFirstChild.cbSize = sizeof(WNDCLASSEX);
            wcexFirstChild.style = CS_HREDRAW | CS_VREDRAW;
            wcexFirstChild.lpfnWndProc = WndProcFirstChild;
            wcexFirstChild.cbClsExtra = 0;
            wcexFirstChild.cbWndExtra = 0;
            wcexFirstChild.hInstance = hInst;
            wcexFirstChild.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wcexFirstChild.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcexFirstChild.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcexFirstChild.lpszMenuName = NULL;
            wcexFirstChild.lpszClassName = szFirstChildWindowClass;
            wcexFirstChild.hIconSm = LoadIcon(wcexFirstChild.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcexFirstChild))
            {
                MessageBox(NULL,
                    _T("Call to RegisterClassEx failed! (wcexFirstChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }


            hWndFirstChild = CreateWindow(
                szFirstChildWindowClass,
                szFirstChildTitle,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100,
                100, 100,
                hWnd,
                NULL,
                hInst,
                NULL
            );

            if (!hWndFirstChild)
            {
                MessageBox(NULL,
                    _T("Call to CreateWindow failed! (hWndFirstChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }

            CreateWindow(TEXT("STATIC"), TEXT("1"),
                WS_VISIBLE | WS_CHILD,
                0, 0, 20, 20,
                hWndFirstChild, (HMENU)NULL, NULL, NULL);

            SetTimer(hWnd, ID_TIMER_4, uFirstDeltaTime, NULL);

            break;
        }
        case ID_TIMER_4: {
            KillTimer(hWnd, ID_TIMER_4);

            WNDCLASSEX wcexFourthChild;

            wcexFourthChild.cbSize = sizeof(WNDCLASSEX);
            wcexFourthChild.style = CS_HREDRAW | CS_VREDRAW;
            wcexFourthChild.lpfnWndProc = WndProcFirstChild;
            wcexFourthChild.cbClsExtra = 0;
            wcexFourthChild.cbWndExtra = 0;
            wcexFourthChild.hInstance = hInst;
            wcexFourthChild.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wcexFourthChild.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcexFourthChild.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcexFourthChild.lpszMenuName = NULL;
            wcexFourthChild.lpszClassName = szFourthChildWindowClass;
            wcexFourthChild.hIconSm = LoadIcon(wcexFourthChild.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcexFourthChild))
            {
                MessageBox(NULL,
                    _T("Call to RegisterClassEx failed! (wcexFourthChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }


            hWndFourthChild = CreateWindow(
                szFourthChildWindowClass,
                szFourthChildTitle,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                300, 300,
                100, 100,
                hWnd,
                NULL,
                hInst,
                NULL
            );

            if (!hWndFourthChild)
            {
                MessageBox(NULL,
                    _T("Call to CreateWindow failed! (hWndFourthChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }

            CreateWindow(TEXT("STATIC"), TEXT("4"),
                WS_VISIBLE | WS_CHILD,
                0, 0, 20, 20,
                hWndFourthChild, (HMENU)NULL, NULL, NULL);

            SetTimer(hWnd, ID_TIMER_5, uSecondDeltaTime, NULL);

            break;
        }
        case ID_TIMER_5: {

            KillTimer(hWnd, ID_TIMER_5);

            SetWindowPos(hWndFirstChild, HWND_TOP, 0, 0, 150, 150, SWP_NOMOVE);

            SetTimer(hWnd, ID_TIMER_6, uSecondDeltaTime, NULL);

            break;
        }
        case ID_TIMER_6: {

            KillTimer(hWnd, ID_TIMER_6);

            SetWindowPos(hWndSecondChild, HWND_TOP, 0, 0, 150, 150, SWP_NOMOVE);

            SetTimer(hWnd, ID_TIMER_7, uSecondDeltaTime, NULL);

            break;
        }
        case ID_TIMER_7: {

            KillTimer(hWnd, ID_TIMER_7);

            SetWindowPos(hWndThirdChild, HWND_TOP, 0, 0, 150, 150, SWP_NOMOVE);

            SetTimer(hWnd, ID_TIMER_8, uSecondDeltaTime, NULL);

            break;
        }
        case ID_TIMER_8: {

            KillTimer(hWnd, ID_TIMER_8);

            SetWindowPos(hWndFourthChild, HWND_TOP, 0, 0, 150, 150, SWP_NOMOVE);

            break;
        }
        default:
            break;
        }
        break;

        case WM_KEYDOWN: {
            switch (wParam)
            {
            case VK_CONTROL:

                bControlFlag = true;
                MessageBox(NULL,
                    _T("CTRL down"),
                    _T("MSG"),
                    NULL);

                break;

            default:
                break;
            }

            break;
        }

        case WM_KEYUP: {
            switch (wParam)
            {
            case VK_CONTROL:

                bControlFlag = false;

                MessageBox(NULL,
                    _T("CTRL up"),
                    _T("MSG"),
                    NULL);

                break;

            default:
                break;
            }

            break;
        }

        case WM_CHAR: {

            switch (wParam)
            {
            case 0x31:      //клавиша 1

                if (bControlFlag) {
                    //MessageBox(NULL,
                    //    _T("CTRL + 1"),
                    //    _T("MSG"),
                    //    NULL);

                    DeleteObject(brush);
                    brush = CreateSolidBrush(RGB(0, 255, 0));

                    SetClassLongPtr(hWndFirstChild, GCL_HBRBACKGROUND, (LONG)brush);
                    InvalidateRect(hWndFirstChild, NULL, TRUE);
                }
                
                break;

            case 0x32:      //клавиша 2

                if (bControlFlag) {
                    //MessageBox(NULL,
                    //    _T("CTRL + 2"),
                    //    _T("MSG"),
                    //    NULL);

                    DeleteObject(brush);
                    brush = CreateSolidBrush(RGB(255, 0, 0));

                    SetClassLongPtr(hWndSecondChild, GCL_HBRBACKGROUND, (LONG)brush);
                    InvalidateRect(hWndSecondChild, NULL, TRUE);

                }

                break;

            case 0x33:      //клавиша 3

                if (bControlFlag) {
 /*                   MessageBox(NULL,
                        _T("CTRL + 3"),
                        _T("MSG"),
                        NULL);*/
                    DeleteObject(brush);
                    brush = CreateSolidBrush(RGB(0, 0, 255));

                    SetClassLongPtr(hWndThirdChild, GCL_HBRBACKGROUND, (LONG)brush);
                    InvalidateRect(hWndThirdChild, NULL, TRUE);
                }

                break;

            case 0x34:      //клавиша 4

                if (bControlFlag) {
                    //MessageBox(NULL,
                    //    _T("CTRL + 4"),
                    //    _T("MSG"),
                    //    NULL);
                    DeleteObject(brush);
                    brush = CreateSolidBrush(RGB(255, 255, 0));

                    SetClassLongPtr(hWndFourthChild, GCL_HBRBACKGROUND, (LONG)brush);
                    InvalidateRect(hWndFourthChild, NULL, TRUE);
                }

                break;

            default:
                break;
            }

            break;
        }



    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}




LRESULT CALLBACK WndProcFirstChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}