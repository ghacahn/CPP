// WindowsProject1.cpp : ���������� ����� ����� ��� ����������.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <iostream>
#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

struct color
{
    int R;
    int G;
    int B;
};

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

    // TODO: ���������� ��� �����.

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // ���� ��������� ���������:
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
//  �������: MyRegisterClass()
//
//  ����: ������������ ����� ����.
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
//   �������: InitInstance(HINSTANCE, int)
//
//   ����: ��������� ������ ���������� � ������� ������� ����
//
//   �����������:
//
//        � ���� ������� ������ ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    hInst = hInstance; // ��������� ������ ���������� � ���������� ����������

    hWnd = CreateWindow(szWindowClass, L"������", WS_OVERLAPPEDWINDOW,
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
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: ������������ ��������� � ������� ����.
//
//  WM_COMMAND  - ���������� ���� ����������
//  WM_PAINT    - ��������� �������� ����
//  WM_DESTROY  - ��������� ��������� � ������ � ���������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hDeviceContext;
    HPEN hPen;
    PAINTSTRUCT ps;
    static int sx, sy;
    switch (message)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        // ��������� ����� � ����:
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
    case WM_PAINT:
    {
        hDeviceContext = BeginPaint(hWnd, &ps);
        // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        HWND hWindow = GetConsoleWindow();
        //HDC hDeviceContext = GetDC(hWindow);
        //������ ����
        HPEN hPen1 = CreatePen(PS_SOLID, 30, RGB(255, 0, 0));
        HPEN hPen2 = CreatePen(PS_SOLID, 30, RGB(255, 255, 255));
        int rad = 15;
        COORD shar;
        shar.X = rand() % sx;
        shar.Y = rand() % sy;
         int pribx = 1; int priby = 1; int sleepy = 10;
        while (1)
        {
            SetConsoleCursorPosition(hStdout, shar);
            SelectObject(hDeviceContext, hPen2);
            Ellipse(hDeviceContext, shar.Y - rad, rad + shar.X, rad + shar.Y, shar.X - rad);
            if (shar.X - 25 == sy || shar.X - 25 == 0)
            {
                pribx = -pribx;
                hPen1 = CreatePen(PS_SOLID, 30, RGB(255, 255, 0));
                SelectObject(hDeviceContext, hPen1);
                sleepy += 10;
                MessageBeep(MB_ICONHAND);
            }
            if (shar.Y - 25 == sx || shar.Y - 25 == 0)
            {
                priby = -priby;
                hPen1 = CreatePen(PS_SOLID, 30, RGB(0, 255, 0));
                SelectObject(hDeviceContext, hPen1);
                sleepy -= 5;
                MessageBeep(MB_OK);
            }
            shar.X += pribx; shar.Y += priby;
            SetConsoleCursorPosition(hStdout, shar);
            SelectObject(hDeviceContext, hPen1);
            Ellipse(hDeviceContext, shar.Y - rad, rad + shar.X, rad + shar.Y, shar.X - rad);
            Sleep(sleepy);
        }
        // ������� ������� 
        DeleteObject(hPen1);
        DeleteObject(hPen2);
        EndPaint(hWnd, &ps);
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

// ���������� ��������� ��� ���� "� ���������".
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
