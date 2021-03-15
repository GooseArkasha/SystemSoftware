#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Глобальные переменные

// Название классов окон
static TCHAR szWindowClass[] = _T("MainWindow");  
static TCHAR szFirstChildWindowClass[] = _T("FirstChildWindow");
static TCHAR szSecondChildWindowClass[] = _T("SecondChildWindow");

// TCHAR - не отдельный тип данных, это макрос,
// который в зависимости от настроек кодировки проекта транслируется в char (каждый символ строки занимает 1 байт, чаще всего кодировка ANSI) 
// или wchar_t (каждый символ занимает 2 байта, UNICODE)

// Префикс L перед строкой делает ее UNICODE строкой
// Префикс _T - это макрос, то есть при компиляции строка становится ANSI-строкой или UNICODE-строкой

// Заголовки окон
static TCHAR szTitle[] = _T("C0");
static TCHAR szFirstChildTitle[] = _T("C1");
static TCHAR szSecondChildTitle[] = _T("C2");


// Дескриптор экземпляра приложения. Префикс H (handle) означает, что переменная - дескриптор
HINSTANCE hInst;


// Функции обработки сообщений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FirstChildProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SecondChildProc(HWND, UINT, WPARAM, LPARAM);

// LRESULT - значение, возвращаемое оконной процедурой. Имеет тип long
// CALLBACK - функция обратного вызова. То есть ее исходный код передается в качестве аргумента другой функции.
// Это позволяет в процедуре выполнять код функции, недоступный для прямого вызова


// Основная функция. Аналог main() в консольных приложениях
int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,                   // Дескриптор экземплара приложения. Дескриптор - идентефикатор, по которой ОС отличает один элемент от осталных
    _In_opt_ HINSTANCE hPrevInstance,           // Дескриптор предыдущего экземпляра приложения. Этот дескриптор остался от старых версий Windows. Сейчас в Win32 не используется
    _In_ LPSTR     lpCmdLine,                   // LPSTR - long pointer string, длинный указатель на строку. Используется, если мы запускаем программу через командную строку с прописью парметров
    _In_ int       nCmdShow                     // Режим отображения окна
)
{   
    // Создаем экземплая класса окна, инициализируем поля данных ( WNDCLASSEX - структура на самом деле)
    WNDCLASSEX mainWCEX;            

    mainWCEX.cbSize = sizeof(WNDCLASSEX);                           // Размер структуры в байтах
    mainWCEX.style = CS_HREDRAW | CS_VREDRAW;                       // Стиль класса окошка
    mainWCEX.lpfnWndProc = WndProc;                                 // Указатель на пользовательскую функцию обработки сообщений
    mainWCEX.cbClsExtra = 0;                                        // Число осовобождаемых байтов при создании экземпляра приложения
    mainWCEX.cbWndExtra = 0;                                        // Число освобождаемых байтов в конце структуры
    mainWCEX.hInstance = hInstance;                                 // Дескриптор экземпляра приложения
    mainWCEX.hIcon = LoadIcon(hInstance, IDI_APPLICATION);          // Дескрптор иконки
    mainWCEX.hCursor = LoadCursor(NULL, IDC_ARROW);                 // Дескриптор курсора мыши
    mainWCEX.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));            // Дескриптор цвета фона окошка
    mainWCEX.lpszMenuName = NULL;                                   // Указатель на константную строку, содержащуюю имя меню
    mainWCEX.lpszClassName = szWindowClass;                         // Указатель на константную строку, содержащуюю имя класса
    mainWCEX.hIconSm = LoadIcon(mainWCEX.hInstance, IDI_APPLICATION);   // Дескриптор маленькой иконки, которая ассоциируется с классом окна

    
    // Проверка регистрации класса
    if (!RegisterClassEx(&mainWCEX))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

 
    hInst = hInstance;      // Присваиваем переменной hInst (переменная дескриптора экземпляра приложения) дескриптор экземпляра приложения, в качестве аргумента функции WinMain


    // Создаем дескриптор окашка и инициализируем его значением дескриптора, возвращаемым функцией CreateWindow, которая создает окошко
    HWND hWnd = CreateWindow(
        szWindowClass,                      // Имя окна (глобальная переменная)
        szTitle,                            // Название окошка
        WS_OVERLAPPEDWINDOW,                // Режим отображения окошка
        CW_USEDEFAULT, CW_USEDEFAULT,       // Координаты начального положения окошка
        600, 500,                           // Ширина и высота окошка по умолчанию
        NULL,                               // Дескриптор родительского окошка
        NULL,                               // Дескриптор меню
        hInstance,                          // Дескриптор экземпляра приложения
        NULL                                // lpParam 
    );


    // Проверяем, создано ли окно
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Функция отображения окна на экране ПК. Первыый парам. - дескриптор окна, второй - режим отображения
    ShowWindow(hWnd,
        nCmdShow);

    // Функция обновления окошка на экране при сворачивании или при динамической информации. Параметр - дескриптор окна
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


    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(  // Обрабатывает сообщения, посылаемые ОС
        &msg,           // Указатель на структуру Msg, в нее помещается очередное сообщение
        NULL,           // Дескриптор окошка
        0,              // Фильтры
        0               // Фильтры для выборки сообщений
    ))
    {
        TranslateMessage(&msg);  // Нужна для интерпретации сообщений
        DispatchMessage(&msg);   // Нужна для интерпретации сообщений
    }

    return (int)msg.wParam;
}

// Функция обработки сообщений
LRESULT CALLBACK WndProc(
    HWND hWnd,                  // Дескриптор окошка
    UINT message,               // Сообщение, посылаемое ОС
    WPARAM wParam,              // Параметры сообщений для последующего обращения
    LPARAM lParam               // Параметры сообщений для последующего обращения
)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);     //Посылает WinMain сообщение о выходе WM_QUIT, что останавливает цикл обработки сообщений в WinMain
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