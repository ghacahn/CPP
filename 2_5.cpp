// WindowsProject1.cpp : ���������� ����� ����� ��� ����������.
//

#include "framework.h"
#include "WindowsProject2.h"
#include <iostream>
#define MAX_LOADSTRING 100
#define IDB_BITMAP1 200

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
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

    hWnd = CreateWindow(szWindowClass, L"������ � ������������", WS_OVERLAPPEDWINDOW,
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

void MyMenu(HWND hWnd)
{
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(SubMenu, MF_STRING, 1, L"��������");
    AppendMenu(SubMenu, MF_STRING, 2, L"�������");
    AppendMenu(SubMenu, MF_STRING, 3, L"�������� �����������");
    AppendMenu(SubMenu, MF_STRING, 4, L"����");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"�����������");
    SetMenu(hWnd, RootMenu);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hDeviceContext;
    PAINTSTRUCT ps;
    static BITMAP bm;
    HBITMAP hBitmap;
    static HDC memBit;
    static int caption, menu, border;
    switch (message)
    {
    case WM_CREATE:
        MyMenu(hWnd);
        caption = GetSystemMetrics(SM_CYCAPTION);
        menu = GetSystemMetrics(SM_CYMENU);
        border = GetSystemMetrics(SM_CXFIXEDFRAME);
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        hBitmap = (HBITMAP)LoadImage(NULL, _T("C:\\Users\\Asus\\Downloads\\WomanAndDog.bmp"),
            IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADFROMFILE);
        GetObject(hBitmap, sizeof(bm), &bm);
        hDeviceContext = GetDC(hWnd);
        memBit = CreateCompatibleDC(hDeviceContext);
        SelectObject(memBit, hBitmap);
        ReleaseDC(hWnd, hDeviceContext);
        break;
    case WM_SIZE:
            MoveWindow(hWnd, 500, 250, bm.bmWidth + 2 * border, bm.bmHeight + caption + menu + border, TRUE);
            break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // ��������� ����� � ����:
        hDeviceContext = GetDC(hWnd);
        switch (wmId)
        {

        case 1:
            BitBlt(hDeviceContext, 0, 0, bm.bmWidth, bm.bmHeight, memBit, 0, 0, SRCCOPY);
            break;
        case 2:
            BitBlt(hDeviceContext, 0, 0, bm.bmWidth, bm.bmHeight, memBit, 0, 0, WHITENESS);
            break;
        case 3:
            BitBlt(hDeviceContext, 0, 0, bm.bmWidth, bm.bmHeight, memBit, 0, 0, DSTINVERT);
            break;
        case 4:
            BitBlt(hDeviceContext, 0, 0, bm.bmWidth, bm.bmHeight, memBit, 0, 0, BLACKNESS);
            break;
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        hDeviceContext = BeginPaint(hWnd, &ps);
        BitBlt(hDeviceContext, 0, 0, bm.bmWidth, bm.bmHeight, memBit, 0, 0, SRCCOPY);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DeleteDC(memBit);
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
