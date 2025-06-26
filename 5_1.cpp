#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

struct link
{
	int data;
	link* next;
};

class linklist
{
protected:
	link* first;
public:
	linklist()
	{
		first = NULL;
	}
	void additem(int d);
	void display();
};

void linklist::additem(int d)
{
	link* newlink = new link;
	newlink->data = d;
	newlink->next = first;
	first = newlink;
}
void linklist::display()
{
	link* current = first;
	while (current)
	{
		cout << current->data << endl;
		current = current->next;
	}
}

class stack_linklist: public linklist
{
public:
	void additem(int d);
	void pop();
};

void stack_linklist::additem(int d)
{
	linklist::additem(d);
	cout << "Добавляем в стек число " << d << endl;
}
void stack_linklist::pop()
{
	if (first == NULL)
	{
		cout << "Стек пуст" << endl;
		exit(0);
	}
	link* current = first;
	cout << "	Извлекаем из стека число " << current->data << endl;
	current = current->next;
	first = current;
}

class queue_linklist : public linklist
{
private:
	int k = 0;
public:
	void additem(int d);
	void pop();
};
void queue_linklist::additem(int d)
{
	linklist::additem(d);
	cout << "Добавляем в очередь число " << d << endl;
	k += 1;
}
void queue_linklist::pop()
{
	if (k == 0)
	{
		cout << "Очередь пуста" << endl;
		exit(0);
	}
	link* current = first;
	for (int i = 1; i < k; i++)
		current = current->next;
	cout << "	Извлекаем из очереди число " << current->data << endl;
	k -= 1;
}

int main()
{
	SetConsoleOutputCP(1251);
	cout << setfill('-') << setw(20) << "Stack" << setw(15) << '-' << endl;
	stack_linklist stack;
	stack.additem(11);
	stack.additem(22);
	stack.additem(33);
	stack.pop();
	stack.additem(44);
	for (int i = 1; i < 4; i++)
	{
		stack.pop();
	}
	cout << endl << setfill('-') << setw(21) << "Queue" << setw(16) << '-' << endl;
	queue_linklist queue;
	queue.additem(11);
	queue.additem(22);
	queue.additem(33);
	queue.pop();
	queue.additem(44);
	for (int i = 1; i < 5; i++)
	{
		queue.pop();
	}
	_getche();
}