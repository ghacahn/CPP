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

class stack_linklist
{
private:
	link* first;
public:
	stack_linklist()
	{
		first = NULL; 
	}
	void additem(int d);
	void display();
	void pop();
};

void stack_linklist::additem(int d)
{
	link* newlink = new link;
	newlink->data = d;
	newlink->next = first;
	first = newlink;
	cout << "Добавляем в стек число " << d << endl;
}
void stack_linklist::display()
{
	link* current = first;
	while (current)
	{
		cout << current->data << endl;
		current = current->next;
	}
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

int main()
{
	SetConsoleOutputCP(1251);
	stack_linklist list;
	list.additem(11);
	list.additem(22);
	list.additem(33);
	list.pop();
	list.pop();
	list.additem(44);
	for (int i = 1; i < 4; i++)
	{
		list.pop();
	}
}