#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Queue
{
private:
	static const int MAX = 10;
	int qu[MAX];
	int head;
	int tail;
	int kolvo_el = 0;
public:
	Queue()
	{
		head = 0;
		tail = 0;
	}
	bool put(int);
	int get();
};
bool Queue::put(int var)
{
	if (tail == MAX)
		tail = 0;
	if (head == tail && kolvo_el != 0)
	{
		cout << "Массив заполнен" << endl;
		return 0;
	}
	kolvo_el += 1;
	qu[tail] = var;
	cout << "Элемент " << qu[tail] << " помещён в очередь. Всего в очереди " << kolvo_el << " элементов" << endl;
	tail++;
	return 1;
}
int Queue::get()
{
	if (head == tail && kolvo_el == 0)
	{
		cout << "Массив пуст" << endl;
		return 0;
	}
	if (head == MAX)
		head = 0;
	kolvo_el -= 1;
	cout << "Элемент " << qu[head] << " извлечён из очереди. Всего в очереди " << kolvo_el << " элементов." << endl;
	return qu[head++];
}

int main()
{
	SetConsoleOutputCP(1251);
	Queue qu1;
	const int n = 10;
	int arr[n] = { 11, 22, 33, 44, 55, 66, 77, 88, 99, 1111 };
	for (int i = 0; i < n; i++)
	{
		qu1.put(arr[i]);
	}
	qu1.put(1212); // попытка добавить лишний элемент
	for (int i = 0; i < n; i++)
	{
		qu1.get();
	}
	qu1.put(1313);
	qu1.get(); 
	qu1.get();// попытка извлечь что-то из пустого массива
	_getche();
}