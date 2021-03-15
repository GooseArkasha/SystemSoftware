#include <windows.h>
#include <WinBase.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>


#define ID_WRITE_BUTTON 1
#define ID_READ_BUTTON_TXT 2
#define ID_READ_BUTTON_BIN 3
#define ID_DUMP_BUTTON_BIN 4
#define ID_SIZEOF_BUTTON 5



static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("PR 2 System Software Popova E.V. IKBO-01-18");
static TCHAR szTextFileName[] = _T("file1.txt");
static TCHAR szBinFileName[] = _T("file2.bin");

const TCHAR szLongTmpl[] = _T("%sLONG, INT: %d\n");
const TCHAR szDwordTmpl[] = _T("%sDWORD, UINT: %u\n");
const TCHAR szDoubleTmpl[] = _T("%sDouble: тут должно быть число, но wsprintf не поддерживает вещественные числа.\n");
const TCHAR szTcharTmpl[] = _T("%sTCHAR: %c\n");
const TCHAR szStrTmpl[] = _T("%sSTR: %s\n");
const TCHAR szBlankTmpl[] = _T("");
const TCHAR szDumpTmpl[] = _T("%s %02X");

HINSTANCE hInst;

HWND hDwordEdit;
HWND hLongEdit;
HWND hDoubleEdit;
HWND hTcharEdit;
HWND hStrEdit;



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        550, 250,
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
    case WM_CREATE: {

        CreateWindow(TEXT("STATIC"), TEXT("Введите значения, которые будут записаны в файлы"),
            WS_VISIBLE | WS_CHILD,
            10, 10, 300, 40,
            hWnd, (HMENU)NULL, NULL, NULL);


        CreateWindow(TEXT("STATIC"), TEXT("DWORD, UINT"),
            WS_VISIBLE | WS_CHILD,
            10, 60, 120, 20,
            hWnd, (HMENU)NULL, NULL, NULL);

        hDwordEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 60, 160, 20,
            hWnd, (HMENU)NULL, NULL, NULL);


        CreateWindow(TEXT("STATIC"), TEXT("LONG, INT"),
            WS_VISIBLE | WS_CHILD,
            10, 90, 120, 20,
            hWnd, (HMENU)NULL, NULL, NULL);

        hLongEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 90, 160, 20,
            hWnd, (HMENU)NULL, NULL, NULL);


        CreateWindow(TEXT("STATIC"), TEXT("DOUBLE"),
            WS_VISIBLE | WS_CHILD,
            10, 120, 120, 20,
            hWnd, (HMENU)NULL, NULL, NULL);

        hDoubleEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 120, 160, 20,
            hWnd, (HMENU)NULL, NULL, NULL);


        CreateWindow(TEXT("STATIC"), TEXT("TCHAR"),
            WS_VISIBLE | WS_CHILD,
            10, 150, 120, 20,
            hWnd, (HMENU)NULL, NULL, NULL);

        hTcharEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 150, 160, 20,
            hWnd, (HMENU)NULL, NULL, NULL);


        CreateWindow(TEXT("STATIC"), TEXT("STR_1"),
            WS_VISIBLE | WS_CHILD,
            10, 180, 120, 20,
            hWnd, (HMENU)NULL, NULL, NULL);

        hStrEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            150, 180, 160, 20,
            hWnd, (HMENU)NULL, NULL, NULL);



        CreateWindow(TEXT("STATIC"), TEXT("Выберите действие"),
            WS_VISIBLE | WS_CHILD,
            320, 10, 200, 40,
            hWnd, (HMENU)NULL, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Запись данных в файлы"),
            WS_VISIBLE | WS_CHILD,
            320, 60, 200, 20,
            hWnd, (HMENU)ID_WRITE_BUTTON, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Считать данные из file1.txt"),
            WS_VISIBLE | WS_CHILD,
            320, 90, 200, 20,
            hWnd, (HMENU)ID_READ_BUTTON_TXT, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Считать данные из file2.bin"),
            WS_VISIBLE | WS_CHILD,
            320, 120, 200, 20,
            hWnd, (HMENU)ID_READ_BUTTON_BIN, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Дамп файла file2.bin"),
            WS_VISIBLE | WS_CHILD,
            320, 150, 200, 20,
            hWnd, (HMENU)ID_DUMP_BUTTON_BIN, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("sizeof()"),
            WS_VISIBLE | WS_CHILD,
            320, 180, 200, 20,
            hWnd, (HMENU)ID_SIZEOF_BUTTON, NULL, NULL);

        break;

    }

    case WM_COMMAND:

        HANDLE hFileTXT;
        HANDLE hFileBIN;
        DWORD temp;

        DWORD dwBuffer;
        LONG lBuffer;
        DOUBLE dBuffer;
        TCHAR tcBuffer;
        TCHAR tBuffer[256];
        BYTE bBuffer;
        char cBuffer[256];
        wchar_t wBuffer[256];


        switch (LOWORD(wParam))
        {
        case ID_WRITE_BUTTON: {

            wchar_t* wEndString;
            char* cEndString;

            hFileTXT = CreateFile(szTextFileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);

            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                hFileTXT = CreateFile(szTextFileName,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL, 0);
            }

            if (INVALID_HANDLE_VALUE == hFileTXT) {
                MessageBox(hWnd, _T("Ошибка создания файла"), _T("Read Button MB"), MB_OK);
                return 1;
            }

            hFileBIN = CreateFile(szBinFileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);

            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                hFileBIN = CreateFile(szBinFileName,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL, 0);
            }

            if (INVALID_HANDLE_VALUE == hFileBIN) {
                MessageBox(hWnd, _T("Ошибка создания файла"), _T("Read Button MB"), MB_OK);
                return 1;
            }


            GetWindowTextA(hDwordEdit, cBuffer, sizeof(cBuffer));
            GetWindowTextW(hDwordEdit, wBuffer, sizeof(wBuffer));
            GetWindowText(hDwordEdit, tBuffer, sizeof(tBuffer));


            if (sizeof(TCHAR) == sizeof(char)) {
                dwBuffer = strtoul(cBuffer, &cEndString, 0);
            }
            else {
                dwBuffer = wcstoul(wBuffer, &wEndString, 0);
            }


            WriteFile(hFileTXT, tBuffer, sizeof(tBuffer), &temp, NULL);
            WriteFile(hFileBIN, &dwBuffer, sizeof(dwBuffer), &temp, NULL);
                         


            GetWindowTextA(hLongEdit, cBuffer, sizeof(cBuffer));
            GetWindowTextW(hLongEdit, wBuffer, sizeof(wBuffer));
            GetWindowText(hLongEdit, tBuffer, sizeof(tBuffer));

            if (sizeof(TCHAR) == sizeof(char)) {
                lBuffer = strtol(cBuffer, &cEndString, 0);
            }
            else {
                lBuffer = wcstol(wBuffer, &wEndString, 0);
            }

            WriteFile(hFileTXT, tBuffer, sizeof(tBuffer), &temp, NULL);
            WriteFile(hFileBIN, &lBuffer, sizeof(lBuffer), &temp, NULL);


            GetWindowTextA(hDoubleEdit, cBuffer, sizeof(cBuffer));
            GetWindowTextW(hDoubleEdit, wBuffer, sizeof(wBuffer));
            GetWindowTextW(hDoubleEdit, tBuffer, sizeof(tBuffer));

            if (sizeof(TCHAR) == sizeof(char)) {
                dBuffer = strtod(cBuffer, &cEndString);
            }
            else {
                dBuffer = wcstod(wBuffer, &wEndString);
            }

            WriteFile(hFileTXT, tBuffer, sizeof(tBuffer), &temp, NULL);
            WriteFile(hFileBIN, &dBuffer, sizeof(dBuffer), &temp, NULL);


            GetWindowText(hTcharEdit, tBuffer, sizeof(tBuffer));

            tcBuffer = tBuffer[0];

            WriteFile(hFileTXT, tBuffer, sizeof(tBuffer), &temp, NULL);
            WriteFile(hFileBIN, &tcBuffer, sizeof(tcBuffer), &temp, NULL);


            GetWindowText(hStrEdit, tBuffer, sizeof(tBuffer));

            WriteFile(hFileTXT, tBuffer, sizeof(tBuffer), &temp, NULL);
            WriteFile(hFileBIN, tBuffer, sizeof(tBuffer), &temp, NULL);

            CloseHandle(hFileTXT);
            CloseHandle(hFileBIN);

            break;
        }

        case ID_READ_BUTTON_TXT: {

            wchar_t* wEndString;
            char* cEndString;

            hFileTXT = CreateFile(szTextFileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);

            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                hFileTXT = CreateFile(szTextFileName,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL, 0);
            }

            if (INVALID_HANDLE_VALUE == hFileTXT) {
                MessageBox(hWnd, _T("Ошибка создания файла"), _T("Read Button MB"), MB_OK);
                return 1;
            }
            


            if (ReadFile(hFileTXT, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, _T("DWORD, UINT: %s;\n"), wBuffer);
            }
            

            if (ReadFile(hFileTXT, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, _T("%sLONG, INT: %s;\n"), tBuffer, wBuffer);
            }
            
            
            if (ReadFile(hFileTXT, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, _T("%sDOUBLE: %s;\n"), tBuffer, wBuffer);
            }            


            if (ReadFile(hFileTXT, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, _T("%sTCHAR: %s;\n"), tBuffer, wBuffer);
            }
            

            if (ReadFile(hFileTXT, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, _T("%sSTR: %s;\n"), tBuffer, wBuffer);
            }            

            MessageBox(hWnd, tBuffer, _T(".TXT"), MB_OK);

            CloseHandle(hFileTXT);

            break;
        }
        case ID_READ_BUTTON_BIN: {

            hFileBIN = CreateFile(szBinFileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);

            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                hFileBIN = CreateFile(szBinFileName,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL, 0);
            }

            if (INVALID_HANDLE_VALUE == hFileBIN) {
                MessageBox(hWnd, _T("Ошибка создания файла"), _T("Read Button MB"), MB_OK);
                return 1;
            }

            wsprintf(tBuffer, _T(""));

            
            if(ReadFile(hFileBIN, &dwBuffer, sizeof(dwBuffer), &temp, NULL)) {
                wsprintf(tBuffer, szDwordTmpl, tBuffer, dwBuffer);
            }
            

            if (ReadFile(hFileBIN, &lBuffer, sizeof(lBuffer), &temp, NULL)) {
                wsprintf(tBuffer, szLongTmpl, tBuffer, lBuffer);
            }

            if (ReadFile(hFileBIN, &dBuffer, sizeof(dBuffer), &temp, NULL)) {
                wsprintf(tBuffer, szDoubleTmpl, tBuffer);
            }


            if (ReadFile(hFileBIN, &tcBuffer, sizeof(tcBuffer), &temp, NULL)) {
                wsprintf(tBuffer, szTcharTmpl, tBuffer, tcBuffer);
            }


            if (ReadFile(hFileBIN, wBuffer, sizeof(tBuffer), &temp, NULL)) {
                wsprintf(tBuffer, szStrTmpl, tBuffer, wBuffer);
            }
            
            
            MessageBox(hWnd, tBuffer, _T(".BIN"), MB_OK);


            CloseHandle(hFileBIN);

            break;
        }

        case ID_DUMP_BUTTON_BIN: {

            hFileBIN = CreateFile(szBinFileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);

            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                hFileBIN = CreateFile(szBinFileName,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL, 0);
            }

            if (INVALID_HANDLE_VALUE == hFileBIN) {
                MessageBox(hWnd, _T("Ошибка создания файла"), _T("Read Button MB"), MB_OK);
                return 1;
            }

            wsprintf(tBuffer, szBlankTmpl);

            INT iLength = GetFileSize(hFileBIN, NULL);

            for (int i = 0; i < 32; i++) {

                if (i % 16 == 0) {
                    wsprintf(tBuffer, _T("%s\n"), tBuffer);
                }

                if (ReadFile(hFileBIN, &bBuffer, sizeof(bBuffer), &temp, NULL)) {

                    wsprintf(tBuffer, szDumpTmpl, tBuffer, bBuffer);

                }
            }

            MessageBox(hWnd, tBuffer, _T("Dump .BIN"), MB_OK);

            CloseHandle(hFileBIN);

            break;
        }
        case ID_SIZEOF_BUTTON: {

            const TCHAR szSizeOfTmpl[] = _T("BYTE: %d;\nUINT: %d;\nINT: %d;\nWORD: %d;\nDWORD: %d;\nLONG: %d;\nBOOL: %d;\nFLOAT: %d;\nDOUBLE: %d;\nCHAR: %d;\nTCHAR: %d;");
            wsprintf(tBuffer, szSizeOfTmpl, sizeof(BYTE), sizeof(UINT), sizeof(INT), sizeof(WORD), sizeof(DWORD), sizeof(LONG), sizeof(BOOL), sizeof(FLOAT), sizeof(DOUBLE), sizeof(CHAR), sizeof(TCHAR));
            MessageBox(hWnd, tBuffer, _T("SizeOfButton MB"), MB_OK);

            break;
        }
        default:
            break;
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