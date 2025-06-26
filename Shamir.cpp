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
	int step = a;
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

int f_el(int p, int mod)
{
	int funk_el = 1;
	for (int i = 2; i <= p; i++)
	{
		int k = 0;
		if (prost(i) == 0)
			continue;
		if (p % i == 0)
		{
			while (p % i == 0)
			{
				p /= i;
				k += 1;
			} 
			funk_el *= (stepen(i, k - 1, mod) * (i - 1));
		}
		if (p < 2)
			break;
	}
	cout << endl;
	return funk_el;
}

int main()
{
	SetConsoleOutputCP(1251);	
	cout << setw(59) << "����� ������" << endl << endl;

	cout << setw(120) << "���� ������ " << endl;
	line();

	int p, a, b;
	cout << "������� ������� ������� ����� �: ";
	cin >> p;
	while (prost(p) == 0)
	{
		cout << "��� ����� �� �������. ��������� ������� �����." << endl;
		cout << "������� ������� ������� ����� �: ";
		cin >> p;
	}
	cout << endl << "������� ����� a, ������� ������� � (� - 1): ";
	cin >> a;
	while (nod(a, (p - 1)) != 1)
	{
		cout << "��� ����� �� ������� ������� � (p - 1). ��������� ������� �����." << endl;
		cout << "������� ����� a, ������� ������� � (� - 1): ";
		cin >> a;
	}
	cout << "������� ����� b, ������� ������� � (� - 1): ";
	cin >> b;
	while (nod(b, (p - 1)) != 1)
	{
		cout << "��� ����� �� ������� ������� � (p - 1). ��������� ������� �����." << endl;
		cout << "������� ����� b, ������� ������� � (� - 1): ";
		cin >> b;
	}
	int fun_el = f_el(p - 1, p - 1);
	int obr_a = stepen(a, (fun_el - 1), (p - 1)) % (p - 1);
	int obr_b = stepen(b, (fun_el - 1), (p - 1)) % (p - 1);
	int k;
	cout << "������� ���� k (����� �� 1 �� " << p - 2 << "): ";
	cin >> k;
	while (k < 1 || k > p - 2)
	{
		cout << "��� ����� �� ������ � �������� ��������. ��������� ������� �����." << endl;
		cout << "������� ����: ";
		cin >> k;
	}

	cout << setw(120) << "�������������� �������� " << endl;
	line();
	int M1 = stepen(k, a, p) % p;
	cout << "M1 = (k ^ a) mod p = " << M1 << endl;
	int M2 = stepen(M1, b, p) % p;
	cout << "M2 = (M1 ^ b) mod p = " << M2 << endl;
	int M3 = stepen(M2, obr_a, p) % p;
	cout << "M3 = (M2 ^ (a ^ -1)) mod p = " << M3 << endl;
	int kr = stepen(M3, obr_b, p) % p;

	cout << setw(120) << "�������� ����� " << endl;
	line();
	cout << "k = (M3 ^ (b ^ -1)) mod p = " <<  kr << endl;

	_getche();
}