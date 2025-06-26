#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

const int MAX = 5;
class Stack
{
private:
	int st[MAX];
	int top;
public:
	Stack()
	{
		top = -1;
	}
	void put(int var)
	{
		st[++top] = var;
	}
	int pop()
	{
		return st[top--];
	}
};

class Queue
{
private:
	Stack st1;
	Stack st2;
	int k = 0;
public:
	void put(int var);
	int pop();
};

void Queue::put(int var)
{
	if (k == MAX)
	{
		cout << "������� �����������." << endl;
		exit(0);
	}
	k += 1;
	cout << "������� " << var << " ������� � �������. ����� � ������� " << k << " ���������." << endl;
	st1.put(var);
}
int Queue::pop()
{
	if (k == 0)
	{
		cout << "������� �����." << endl;
		exit(0);
	}
	k -= 1;
	for (int i = 0; i < MAX; i++)
	{
		int var = st1.pop();
		st2.put(var);
	}
	int ret = st2.pop();
	for (int i = 0; i < MAX; i++)
	{
		int var = st2.pop();
		st1.put(var);
	}
	cout << "������� " << ret << " �������� �� �������. ����� � ������� " << k << " ���������." << endl;
	return ret;
}

int main()
{
	SetConsoleOutputCP(1251);
	Queue q1;
	int num[MAX] = {11, 22, 33, 44, 55};
	for (int i = 0; i < MAX; i++)
	{
		q1.put(num[i]);
	}
	//q1.put(66); //������� �������� ����� � ����������� �������
	for (int i = 0; i < MAX; i++)
	{
		q1.pop();
	}
	q1.pop(); //������� ������� ����� �� ������ �������
	_getche();
}