#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;
 
int prost(int a)
{
	for (int i = 2; i <= sqrt(a); i++) 
	{
		if (a % i == 0) 
		{
			return 0;
		}
	}
	if (a <= 1)
		return 0;
	return 1;
}

int nod(int a,  int b)
{
	return b ? nod(b, a % b) : a;
}

int stepen(int a, int b, int mod)
{
	int step = a;
	for (int i = 1; i < b; i++)
	{
		step *= a;
		step %= mod;
	}
	return step;
}

int pervoobraznii_koren(int p, int prov, int vivod)
{
	int pr = 0;
	int f_el = p - 1;
	int flag = 0;
	for (int g = 2; g < f_el; g++)
	{
		if (nod(g, p) != 1)
			continue;
		int step_g = stepen(g, (f_el / 2), p);
		if ((step_g % p) != (p - 1))
			continue; 
		
		flag = 0;
		for (int i = 2; i < f_el; i++)
		{
			if (f_el % i == 0 && prost(i) == 1)
			{
				int l = f_el / i;
				int step_gl = stepen(g, l, p);
				if (step_gl % p == 1)
					flag = 1;
			}
		}
		if (flag == 0)
		{
			if (vivod == 1)
				cout << g << " ";
			if (g == prov)
				pr = 1;
		}
	}
	if (pr == 1)
		return 1;
	if (pr == 0)
		return 0;
}

void line()
{
	for (int i = 1; i < 121; i++)
		cout << "~";
	cout << endl;
}

int main()
{
	SetConsoleOutputCP(1251);
	cout << setw(59) << "Шифрование Эль-Гамаля" << endl << endl;
	cout << setw(119) << "Формируем открытый ключ" << endl;
	line();
	int p;
	cout << "Введите простое число р: ";
	cin >> p;
	while (prost(p) == 0)
	{
		cout << "Это число не простое. Повторите попытку ввода." << endl;
		cout << "Введите простое число р: ";
		cin >> p;
	}
	int g;
	cout << "Введите число g, такое, что g - первообразный корень p (возможные g: ";
	pervoobraznii_koren(p, 1, 1);
	cout << "): ";
	cin >> g;
	while (pervoobraznii_koren(p, g, 0) == 0)
	{
		cout << "Это число g не является первообразным корнем < p. Повторите попытку ввода." << endl;
		cout << "Введите g: ";
		cin >> g;
	}
	int x;
	cout << "Выберите случайное число от 2 до " << p - 2 << " (это число - секретный ключ) : ";
	cin >> x;
	while (x <= 1 || x >= p - 1)
	{
		cout << "Это число не входит в заданный диапазон. Повторите попытку ввода." << endl;
		cout << "Выберите случайное число от 2 до " << p - 2 << " :";
		cin >> x;
	}
	int y;
	int st_g = stepen(g, x, p);
	y = st_g % p;
	line();
	cout << endl << "Открытый ключ (p, g, y) = (" << p << ", " << g << ", " << y << ")" << endl;

	cout << endl << setw(119) << "Формируем сообщение" << endl;
	line();

	int k;
	cout << "Выберите случайное число от 2 до "  << p - 1 << " : ";
	cin >> k;
	while (k <= 1 || k >= p - 1)
	{
		cout << "Это число не входит в заданный диапазон. Повторите попытку ввода." << endl;
		cout << "Выберите случайное число от 2 до " << p - 2 << " :";
		cin >> k;
	}
	int message;
	cout << "Введите сообщение (число от 1 до " << p - 1 << "): ";
	cin >> message;
	while (message < 1 || message > p - 1)
	{
		cout << "Это число не входит в заданный диапазон. Повторите попытку ввода." << endl;
		cout << "Выберите сообщение: ";
		cin >> message;
	}
	int u, v;
	int st_gk = stepen(g, k, p);
	int st_yk = stepen(y, k, p);
	u = st_gk % p;
	v = (message * st_yk) % p;
	line();
	cout << endl << "Зашифрованное сообщение (u, v): (" << u << ", " << v << ")" << endl << endl;

	cout << setw(119) << "Расшифровка сообщения" << endl;
	line();
	
	//нахождение обратного числа obr_ux
	int st_ux = stepen(u, x, p);
	int f_el = p - 1;
	int a = stepen(st_ux, (f_el - 1), p);
	int obr_ux = a % p;
	int mess = (obr_ux * v) % p;

	cout << "message = u^(-x)*v (mod p) = " << mess << endl;
	line();
	_getche();
}
