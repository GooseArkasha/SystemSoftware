#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// ���������� ����������

// �������� ������� ����
static TCHAR szWindowClass[] = _T("MainWindow");  
static TCHAR szFirstChildWindowClass[] = _T("FirstChildWindow");
static TCHAR szSecondChildWindowClass[] = _T("SecondChildWindow");

// TCHAR - �� ��������� ��� ������, ��� ������,
// ������� � ����������� �� �������� ��������� ������� ������������� � char (������ ������ ������ �������� 1 ����, ���� ����� ��������� ANSI) 
// ��� wchar_t (������ ������ �������� 2 �����, UNICODE)

// ������� L ����� ������� ������ �� UNICODE �������
// ������� _T - ��� ������, �� ���� ��� ���������� ������ ���������� ANSI-������� ��� UNICODE-�������

// ��������� ����
static TCHAR szTitle[] = _T("C0");
static TCHAR szFirstChildTitle[] = _T("C1");
static TCHAR szSecondChildTitle[] = _T("C2");


// ���������� ���������� ����������. ������� H (handle) ��������, ��� ���������� - ����������
HINSTANCE hInst;


// ������� ��������� ���������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FirstChildProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SecondChildProc(HWND, UINT, WPARAM, LPARAM);

// LRESULT - ��������, ������������ ������� ����������. ����� ��� long
// CALLBACK - ������� ��������� ������. �� ���� �� �������� ��� ���������� � �������� ��������� ������ �������.
// ��� ��������� � ��������� ��������� ��� �������, ����������� ��� ������� ������


// �������� �������. ������ main() � ���������� �����������
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,                   // ���������� ���������� ����������. ���������� - �������������, �� ������� �� �������� ���� ������� �� ��������
    _In_opt_ HINSTANCE hPrevInstance,           // ���������� ����������� ���������� ����������. ���� ���������� ������� �� ������ ������ Windows. ������ � Win32 �� ������������
    _In_ LPSTR     lpCmdLine,                   // LPSTR - long pointer string, ������� ��������� �� ������. ������������, ���� �� ��������� ��������� ����� ��������� ������ � �������� ���������
    _In_ int       nCmdShow                     // ����� ����������� ����
)
{   
    // ������� ��������� ������ ����, �������������� ���� ������ ( WNDCLASSEX - ��������� �� ����� ����)
    WNDCLASSEX mainWCEX;            

    mainWCEX.cbSize = sizeof(WNDCLASSEX);                           // ������ ��������� � ������
    mainWCEX.style = CS_HREDRAW | CS_VREDRAW;                       // ����� ������ ������
    mainWCEX.lpfnWndProc = WndProc;                                 // ��������� �� ���������������� ������� ��������� ���������
    mainWCEX.cbClsExtra = 0;                                        // ����� �������������� ������ ��� �������� ���������� ����������
    mainWCEX.cbWndExtra = 0;                                        // ����� ������������� ������ � ����� ���������
    mainWCEX.hInstance = hInstance;                                 // ���������� ���������� ����������
    mainWCEX.hIcon = LoadIcon(hInstance, IDI_APPLICATION);          // ��������� ������
    mainWCEX.hCursor = LoadCursor(NULL, IDC_ARROW);                 // ���������� ������� ����
    mainWCEX.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));            // ���������� ����� ���� ������
    mainWCEX.lpszMenuName = NULL;                                   // ��������� �� ����������� ������, ����������� ��� ����
    mainWCEX.lpszClassName = szWindowClass;                         // ��������� �� ����������� ������, ����������� ��� ������
    mainWCEX.hIconSm = LoadIcon(mainWCEX.hInstance, IDI_APPLICATION);   // ���������� ��������� ������, ������� ������������� � ������� ����

    
    // �������� ����������� ������
    if (!RegisterClassEx(&mainWCEX))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

 
    hInst = hInstance;      // ����������� ���������� hInst (���������� ����������� ���������� ����������) ���������� ���������� ����������, � �������� ��������� ������� WinMain


    // ������� ���������� ������ � �������������� ��� ��������� �����������, ������������ �������� CreateWindow, ������� ������� ������
    HWND hWnd = CreateWindow(
        szWindowClass,                      // ��� ���� (���������� ����������)
        szTitle,                            // �������� ������
        WS_OVERLAPPEDWINDOW,                // ����� ����������� ������
        CW_USEDEFAULT, CW_USEDEFAULT,       // ���������� ���������� ��������� ������
        600, 500,                           // ������ � ������ ������ �� ���������
        NULL,                               // ���������� ������������� ������
        NULL,                               // ���������� ����
        hInstance,                          // ���������� ���������� ����������
        NULL                                // lpParam 
    );


    // ���������, ������� �� ����
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // ������� ����������� ���� �� ������ ��. ������� �����. - ���������� ����, ������ - ����� �����������
    ShowWindow(hWnd,
        nCmdShow);

    // ������� ���������� ������ �� ������ ��� ������������ ��� ��� ������������ ����������. �������� - ���������� ����
    UpdateWindow(hWnd);



    WNDCLASSEX firstChildWCEX;

    firstChildWCEX.cbSize = sizeof(WNDCLASSEX);
    firstChildWCEX.style = CS_HREDRAW | CS_VREDRAW;
    firstChildWCEX.lpfnWndProc = FirstChildProc;
    firstChildWCEX.cbClsExtra = 0;
    firstChildWCEX.cbWndExtra = 0;
    firstChildWCEX.hInstance = hInst;
    firstChildWCEX.hIcon = LoadIcon(hInst, IDI_APPLICATION);
    firstChildWCEX.hCursor = LoadCursor(NULL, IDC_ARROW);
    firstChildWCEX.hbrBackground = CreateSolidBrush(RGB(0, 100, 0));
    firstChildWCEX.lpszMenuName = NULL;
    firstChildWCEX.lpszClassName = szFirstChildWindowClass;
    firstChildWCEX.hIconSm = LoadIcon(firstChildWCEX.hInstance, IDI_APPLICATION);


    if (!RegisterClassEx(&firstChildWCEX))
    {
        MessageBox(NULL,
            _T("Call to Child RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 0;
    }

    RECT rect;
    GetWindowRect(hWnd, &rect);

    HWND hFirstChildWnd = CreateWindow(
        szFirstChildWindowClass,
        szFirstChildTitle,
        WS_OVERLAPPEDWINDOW,
        rect.right - 400, rect.bottom - 300,
        400, 300,
        hWnd,
        NULL,
        hInst,
        NULL
    );


    if (!hFirstChildWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 0;
    }

    ShowWindow(hFirstChildWnd, SW_NORMAL);
    UpdateWindow(hFirstChildWnd);


    WNDCLASSEX secondChildWCEX;

    secondChildWCEX.cbSize = sizeof(WNDCLASSEX);
    secondChildWCEX.style = CS_HREDRAW | CS_VREDRAW;
    secondChildWCEX.lpfnWndProc = SecondChildProc;
    secondChildWCEX.cbClsExtra = 0;
    secondChildWCEX.cbWndExtra = 0;
    secondChildWCEX.hInstance = hInst;
    secondChildWCEX.hIcon = LoadIcon(hInst, IDI_APPLICATION);
    secondChildWCEX.hCursor = LoadCursor(NULL, IDC_ARROW);
    secondChildWCEX.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));
    secondChildWCEX.lpszMenuName = NULL;
    secondChildWCEX.lpszClassName = szSecondChildWindowClass;
    secondChildWCEX.hIconSm = LoadIcon(secondChildWCEX.hInstance, IDI_APPLICATION);


    if (!RegisterClassEx(&secondChildWCEX))
    {
        MessageBox(NULL,
            _T("Call to Child RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 0;
    }

    GetWindowRect(hFirstChildWnd, &rect);

    HWND hSecondChildWnd = CreateWindow(
        szSecondChildWindowClass,
        szSecondChildTitle,
        WS_OVERLAPPEDWINDOW,
        rect.left + (rect.right - rect.left) / 2  - 200 / 2, rect.top + (rect.bottom - rect.top) / 2 - 100 / 2,
        200, 100,
        hWnd,
        NULL,
        hInst,
        NULL
    );


    if (!hSecondChildWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 0;
    }

    ShowWindow(hSecondChildWnd, SW_NORMAL);
    UpdateWindow(hSecondChildWnd);


    // ���� ��������� ���������
    MSG msg;
    while (GetMessage(  // ������������ ���������, ���������� ��
        &msg,           // ��������� �� ��������� Msg, � ��� ���������� ��������� ���������
        NULL,           // ���������� ������
        0,              // �������
        0               // ������� ��� ������� ���������
    ))
    {
        TranslateMessage(&msg);  // ����� ��� ������������� ���������
        DispatchMessage(&msg);   // ����� ��� ������������� ���������
    }

    return (int)msg.wParam;
}

// ������� ��������� ���������
LRESULT CALLBACK WndProc(
    HWND hWnd,                  // ���������� ������
    UINT message,               // ���������, ���������� ��
    WPARAM wParam,              // ��������� ��������� ��� ������������ ���������
    LPARAM lParam               // ��������� ��������� ��� ������������ ���������
)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);     //�������� WinMain ��������� � ������ WM_QUIT, ��� ������������� ���� ��������� ��������� � WinMain
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }

    return 0;
}

LRESULT CALLBACK FirstChildProc(HWND child, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);     
        break;
    default:
        return DefWindowProc(child, message, wParam, lParam);
        break;
    }

    return 0;
}

LRESULT CALLBACK SecondChildProc(HWND hSecondChildWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hSecondChildWnd, message, wParam, lParam);
        break;
    }

    return 0;
}