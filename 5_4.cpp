#include "5_4_ellipse.h"

int main()
{
	
	ellipse c1, c2, c3, c4, c5, c6, c7, c8, c9;
	c1.set_ellipse({ 350, 350 }, 25, 70, { 255, 255, 0 });
	c2.set_ellipse({ 430, 350 }, 25, 70, { 255, 255, 0 });
	//c3 - конструктор
	c4.set_ellipse({ 510, 130 }, 55, 20, { 255, 255, 0 });
	c5.set_ellipse({ 270, 130 }, 55, 20, { 255, 255, 0 });
	c6.set_ellipse({ 390, 50 }, 40, 40, { 255, 255, 0 });
	c7.set_ellipse({ 390, 70 }, 8, 3, { 255, 0, 0 });
	c8.set_ellipse({ 375, 40 }, 2, 2, { 0, 0, 0 });
	c9.set_ellipse({ 405, 40 }, 2, 2, { 0, 0, 0 });
	ellipse el[9] = { c1, c2, c4, c5, c6, c7, c8, c9, c3 };
	for (int i = 0; i < 9; i++)
	{
		el[i].draw_ellipse();
	}
	_getche();
}