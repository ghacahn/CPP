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
	cout << endl << setw(80) << "�������� �������� ������� �� ������ RSA" << endl << endl;
	cout << setw(120) << "���� ������ " << endl;
	line();

	cout << "������� ������� ������� ����� P: ";
	cin >> P;
	while (prost(P) == 0)
	{
		cout << "��� ����� �� �������. ��������� ������� �����." << endl;
		cout << "������� ������� ������� ����� P: ";
		cin >> P;
	}
	cout << "������� ������� ������� ����� Q: ";
	cin >> Q;
	while (prost(Q) == 0)
	{
		cout << "��� ����� �� �������. ��������� ������� �����." << endl;
		cout << "������� ������� ������� ����� Q: ";
		cin >> Q;
	}
	N = P * Q;
	fun_el = (Q - 1) * (P - 1);
	cout << "�������� ����� ����� K0 (1 < K0 < " << fun_el << "), ������� ������� � " << fun_el << ": ";
	cin >> K0;
	while (nod(K0, fun_el) != 1)
	{
		cout << "��� ����� �� ������� ������� � " << fun_el << ".��������� ������� �����." << endl;
		cout << "�������� ����� ����� K0 (1 < K0 < " << fun_el << "), ������� ������� � " << fun_el << ": ";
		cin >> K0;
	}
	int f_el_K0 = f_el(fun_el, fun_el);
	Kc = stepen(K0, (f_el_K0 - 1), fun_el);
	cout << "������� ��������� � (1 < M < " << N << "): "; 
	cin >> M;
	while (M <= 1 || M >= N)
	{
		cout << "��� ����� �� ������ � �������� ��������. ��������� ������� �����." << endl;
		cout << "������� ��������� � (1 < M < " << N << "): ";
		cin >> M;
	}
	int C = stepen(M, Kc, N) % N;

	cout << setw(120) << "����������� ��������� " << endl;
	line();
	cout << "{C, M} = {" << C << ", " << M << "}" << endl;

	cout << setw(120) << "�������� ����������� ������� " << endl;;
	line();
	int Prov = stepen(C, K0, N) % N;
	cout << "M' = C ^ K0 (mod N) = " << Prov << endl;
	if (Prov == M)
		cout << "M' = M, ������� ��������" << endl;
	else
		cout << "M' != M, ������� �� ��������" << endl;
	_getche();
}