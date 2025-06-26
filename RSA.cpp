#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;


void line()
{
	for (int i = 1; i < 121; i++)
		cout << "~";
	cout << endl;
}

int stepen(int a, int b, int mod)
{
	if (b == 0)
		return 1;
	unsigned long step = a;
	for (int i = 1; i < b; i++)
	{
		step *= a;
		step %= mod;
	}
	return step;
}

int nod(int a, int b)
{
	return b ? nod(b, a % b) : a;
}

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

int f_el(int P, int mod)
{
	int funk_el = 1;
	for (int i = 2; i <= P; i++)
	{
		int k = 0;
		if (prost(i) == 0)
			continue;
		if (P % i == 0)
		{
			while (P % i == 0)
			{
				P /= i;
				k += 1;
			}
			funk_el *= (stepen(i, k - 1, mod) * (i - 1));
		}
		if (P < 2)
			break;
	}
	cout << endl;
	return funk_el;
}

int main()
{
	SetConsoleOutputCP(1251);
	int P, Q, N, fun_el, M, Kc, K0;
	cout << endl << setw(80) << "Алгоритм цифровой подписи на основе RSA" << endl << endl;
	cout << setw(120) << "Ввод данных " << endl;
	line();

	cout << "Введите большое простое число P: ";
	cin >> P;
	while (prost(P) == 0)
	{
		cout << "Это число не простое. Повторите попытку ввода." << endl;
		cout << "Введите большое простое число P: ";
		cin >> P;
	}
	cout << "Введите большое простое число Q: ";
	cin >> Q;
	while (prost(Q) == 0)
	{
		cout << "Это число не простое. Повторите попытку ввода." << endl;
		cout << "Введите большое простое число Q: ";
		cin >> Q;
	}
	N = P * Q;
	fun_el = (Q - 1) * (P - 1);
	cout << "Выберите целое число K0 (1 < K0 < " << fun_el << "), взаимно простое с " << fun_el << ": ";
	cin >> K0;
	while (nod(K0, fun_el) != 1)
	{
		cout << "Это число не взаимно простое с " << fun_el << ".Повторите попытку ввода." << endl;
		cout << "Выберите целое число K0 (1 < K0 < " << fun_el << "), взаимно простое с " << fun_el << ": ";
		cin >> K0;
	}
	int f_el_K0 = f_el(fun_el, fun_el);
	Kc = stepen(K0, (f_el_K0 - 1), fun_el);
	cout << "Введите сообщение М (1 < M < " << N << "): "; 
	cin >> M;
	while (M <= 1 || M >= N)
	{
		cout << "Это число не входит в заданный диапазон. Повторите попытку ввода." << endl;
		cout << "Введите сообщение М (1 < M < " << N << "): ";
		cin >> M;
	}
	int C = stepen(M, Kc, N) % N;

	cout << setw(120) << "Подписанное сообщение " << endl;
	line();
	cout << "{C, M} = {" << C << ", " << M << "}" << endl;

	cout << setw(120) << "Проверка подлинности подписи " << endl;;
	line();
	int Prov = stepen(C, K0, N) % N;
	cout << "M' = C ^ K0 (mod N) = " << Prov << endl;
	if (Prov == M)
		cout << "M' = M, подпись подлинна" << endl;
	else
		cout << "M' != M, подпись не подлинна" << endl;
	_getche();
}