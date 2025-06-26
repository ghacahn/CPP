#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

struct color
{
	int R;
	int G;
	int B;
};

class ring
{
private:
	COORD center;
	int radius;
	color col;
	int type;
	int thick;
public:
	ring(): center({ 470, 230 }), radius(100), col({ 255, 255, 0 }), type(1), thick(5) {}
	ring(COORD cen, int r, color c, int t, int th) : center(cen), radius(r), col(c), type(t), thick(th) {}
	void set_ring(COORD, int, color, int, int);
	void show_ring();
};
void ring::set_ring(COORD cen, int r, color c, int t, int th)
{
	center = cen;
	radius = r;
	col = c;
	type = t;
	thick = th;
}
void ring::show_ring()
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
	HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));
	SelectObject(hDeviceContext, hBrush);
	Ellipse(hDeviceContext, center.X - radius, radius + center.Y, radius + center.X, center.Y - radius);
	HPEN hPen = CreatePen(type, thick, RGB(col.R, col.G, col.B));
	SelectObject(hDeviceContext, hPen);
	Ellipse(hDeviceContext, center.X - radius, radius + center.Y, radius + center.X, center.Y - radius);
	DeleteObject(hPen);
	ReleaseDC(hWindow, hDeviceContext);
}

struct link
{
	ring data;
	link* next;
};

class ring_linklist
{
private:
	link* first;
public:
	ring_linklist()
	{
		first = NULL;
	}
	~ring_linklist()
	{

	}
	void add_ring(ring d);
	void display();
	void pop();
};

void ring_linklist::add_ring(ring d)
{
	link* newlink = new link;
	newlink->data = d;
	newlink->next = first;
	first = newlink;
}
void ring_linklist::display()
{
	link* current = first;
	while (current)
	{
		current->data.show_ring();
		current = current->next;
	}
}

void show_list(int k, int type[], int thick[])
{
	ring_linklist list;
	ring r;
	int rad = 70;
	for (int i = 1; i < k; i++)
	{
		r.set_ring({ 470, 230 }, rad, { rand() % 255, rand() % 255, rand() % 255 }, type[i - 1], thick[i - 1]);
		list.add_ring(r);
		rad += 30;
	}
	list.display();
}

int main()
{
	const int r = 10;
	int type[r];
	int thick[r];
	for (int i = 0; i < r; i++)
	{
		type[i] = rand() % 5;
		thick[i] = rand() % 8;
	}
	while (1)
	{
		show_list(r, type, thick);
		Sleep(1000);
	}
}