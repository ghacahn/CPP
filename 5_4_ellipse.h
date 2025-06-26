#pragma once
#include <Windows.h>
#include <conio.h>
using namespace std;

struct color
{
	int R;
	int G;
	int B;
};

class circle
{
protected:
	COORD center;
	int radius;
	color cvet;
public:
	circle(int r = 80, COORD cen = { 390, 200 }, color cv = { 255, 0, 100 }) : radius(r), center(cen), cvet(cv)
	{}
	void set_circle(int, COORD, color);
	void draw_circle();
};

void circle::set_circle(int r, COORD c, color col)
{
	radius = r;
	center = c;
	cvet = col;
}

void circle::draw_circle()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//делаем курсор невидимым
	CONSOLE_CURSOR_INFO curs;
	GetConsoleCursorInfo(hStdout, &curs);
	curs.bVisible = FALSE;
	SetConsoleCursorInfo(hStdout, &curs);
	//
	HWND hWindow = GetConsoleWindow();
	HDC hDeviceContext = GetDC(hWindow);
	//рисуем круг
	HBRUSH hBrush = CreateSolidBrush(RGB(cvet.R, cvet.G, cvet.B));
	SelectObject(hDeviceContext, hBrush);
	Ellipse(hDeviceContext, center.X - radius, radius + center.Y, radius + center.X, center.Y - radius);
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(cvet.R, cvet.G, cvet.B));
	SelectObject(hDeviceContext, hPen);
	Ellipse(hDeviceContext, center.X - radius, radius + center.Y, radius + center.X, center.Y - radius);
	DeleteObject(hPen);
	ReleaseDC(hWindow, hDeviceContext);
}

class ellipse : public circle
{
private:
	int rad_2;
public:
	ellipse() : circle(), rad_2(110) {}
	ellipse(int r2) : circle(), rad_2(r2) {};
	void set_ellipse(COORD, int, int, color);
	void draw_ellipse();
};

void ellipse::set_ellipse(COORD cd, int r1, int r2, color col)
{
	center = cd;
	radius = r1;
	rad_2 = r2;
	cvet = col;
}
void ellipse::draw_ellipse()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//делаем курсор невидимым
	CONSOLE_CURSOR_INFO curs;
	GetConsoleCursorInfo(hStdout, &curs);
	curs.bVisible = FALSE;
	SetConsoleCursorInfo(hStdout, &curs);
	//
	HWND hWindow = GetConsoleWindow();
	HDC hDeviceContext = GetDC(hWindow);
	//рисуем эллипс
	HBRUSH hBrush = CreateSolidBrush(RGB(cvet.R, cvet.G, cvet.B));
	SelectObject(hDeviceContext, hBrush);
	Ellipse(hDeviceContext, center.X - radius, rad_2 + center.Y, radius + center.X, center.Y - rad_2);
	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(cvet.R, cvet.G, cvet.B));
	SelectObject(hDeviceContext, hPen);
	Ellipse(hDeviceContext, center.X - radius, rad_2 + center.Y, radius + center.X, center.Y - rad_2);
	DeleteObject(hPen);
	ReleaseDC(hWindow, hDeviceContext);
}

