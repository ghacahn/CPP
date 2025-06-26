// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <iostream>
#include <conio.h>

#define _USE_MATH_DEFINES
#include <math.h>
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int n = 0;
struct color
{
    int R;
    int G;
    int B;
};

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    hWnd = CreateWindow(szWindowClass, L"Cos", WS_OVERLAPPEDWINDOW,
        150, 0, 1400, 800, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hDeviceContext;
    HPEN hPen;
    PAINTSTRUCT ps;
    int x, y;
    static int sx, sy;
    switch (message)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;

    case WM_PAINT:
    {
        hDeviceContext = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        HWND hWindow = GetConsoleWindow();
        //HDC hDeviceContext = GetDC(hWindow);
        HPEN hPen3 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
        HPEN hPen2 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        HPEN hPen1 = CreatePen(PS_SOLID, 3, RGB(62, 180, 137));
        int a, b, x_scr, y_scr;
        double x, h;
        a = sx / 2;
        b = sy / 2;
        SelectObject(hDeviceContext, hPen1);
        int i;
        for (x = 0, i = 0; x < sx; x += sx / 10, i++)
        {
            if (i != 5)
            {
                MoveToEx(hDeviceContext, x, 0, NULL);
                LineTo(hDeviceContext, x, sy);
            }
        }
        for (y = 0, i = 0; y < sy; y += sy / 10, i++)
        {
            if (i != 5)
            {
                MoveToEx(hDeviceContext, 0, y, NULL);
                LineTo(hDeviceContext, sx, y);
            }
        }
        SelectObject(hDeviceContext, hPen2);
        MoveToEx(hDeviceContext, a, 0, NULL);
        LineTo(hDeviceContext, a, sy);
        MoveToEx(hDeviceContext, 0, b, NULL);
        LineTo(hDeviceContext, sx, b);
        h = 3 * M_PI / a;
        MoveToEx(hDeviceContext, 0, b, NULL);
        SelectObject(hDeviceContext, hPen3);
        for (x = -4 * M_PI, x_scr = 0; x < 4 * M_PI; x += h)
        {
            x_scr = (x + 4 * M_PI) * a / 4 / M_PI;
            y_scr = b - b * cos(x);
            LineTo(hDeviceContext, x_scr, y_scr);
        }
        EndPaint(hWnd, &ps);
        DeleteObject(hPen1);
        DeleteObject(hPen2);
        DeleteObject(hPen3);
    }
    break;
    case WM_KEYDOWN:
    {
        InvalidateRect(hWnd, NULL, TRUE);
        hDeviceContext = BeginPaint(hWnd, &ps);
        HPEN hPen3 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN hPen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HPEN hPen1 = CreatePen(PS_SOLID, 2, RGB(115, 195, 108));
        n += 1;
        int a, b, x_scr, y_scr;
        double x, h;
        a = sx / 2;
        b = sy / 2;
        if (n % 2 == 0)
            SelectObject(hDeviceContext, hPen1);
        else
            SelectObject(hDeviceContext, hPen3);
        int i;
        for (x = 0, i = 0; x < sx; x += sx / 10, i++)
        {
            if (i != 5)
            {
                MoveToEx(hDeviceContext, x, 0, NULL);
                LineTo(hDeviceContext, x, sy);
            }
        }
        for (y = 0, i = 0; y < sy; y += sy / 10, i++)
        {
            if (i != 5)
            {
                MoveToEx(hDeviceContext, 0, y, NULL);
                LineTo(hDeviceContext, sx, y);
            }
        }
        SelectObject(hDeviceContext, hPen2);
        MoveToEx(hDeviceContext, sx / 2, 0, NULL);
        LineTo(hDeviceContext, sx / 2, sy);
        MoveToEx(hDeviceContext, 0, sy/2, NULL);
        LineTo(hDeviceContext, sx, sy / 2);
        h = 3 * M_PI / a;
        MoveToEx(hDeviceContext, 0, b, NULL);
        if (n % 2 == 0)
            SelectObject(hDeviceContext, hPen3);
        else
            SelectObject(hDeviceContext, hPen1);
        for (x = -4 * M_PI, x_scr = 0; x < 4 * M_PI; x += h)
        {
            x_scr = (x + 4 * M_PI) * a / 4 / M_PI;
            y_scr = b - b * cos(x);
            LineTo(hDeviceContext, x_scr, y_scr);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
