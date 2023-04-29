#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <cmath>

using namespace std;
typedef double Info;
struct Elem
{
	Elem* link;
	Info info;
};
void enqueue(Elem*& first, Elem*& last, Info value);
Info dequeue(Elem*& first, Elem*& last);
Info scan(Elem*& first);
void mixQueue(Elem*& firstOfFirst, Elem*& firstOfSecond, Elem*& lastOfFirst, Elem*& lastOfSecond, Elem*& first, Elem*& last);
void lastNotInt(Elem*& first, Elem*& last);
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	Elem* first = NULL,
		* last = NULL;
	Elem* firstOfSecond = NULL,
		* lastOfSecond = NULL;
	Elem* firstOfFirst = NULL,
		* lastOfFirst = NULL;
	int n;
	cout << "Скільки елементів в кожній з черг?" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		enqueue(firstOfFirst, lastOfFirst, (rand() % 10 + 1) * 0.5);
	}
	for (int i = 1; i <= n; i++)
	{
		enqueue(firstOfSecond, lastOfSecond, (rand() % 10 + 1) * 0.5);
	}

	// вилучення та вивід елементів
	Elem* tmp = firstOfFirst;
	cout << "Перший список:  ";
	while (tmp != NULL)
		cout << setw(4) << scan(tmp) << "|";
	cout << endl;
	tmp = firstOfSecond;
	cout << "Другий список:  ";
	while (tmp != NULL)
		cout << setw(4) << scan(tmp) << "|";
	cout << endl;
	mixQueue(firstOfFirst, firstOfSecond, lastOfFirst, lastOfSecond, first, last);
	tmp = first;
	cout << "Мішаний список: ";
	while (tmp != NULL)
		cout << setw(4) << scan(tmp) << "|";
	cout << endl;
	lastNotInt(first, last);
	cout << "Мішаний список: ";
	tmp = first;
	while (tmp != NULL)
		cout << setw(4) << scan(tmp) << "| ";
	cout << endl;
	return 0;
}
void mixQueue(Elem*& firstOfFirst, Elem*& firstOfSecond, Elem*& lastOfFirst, Elem*& lastOfSecond, Elem*& first, Elem*& last)
{
	while (firstOfFirst != NULL && firstOfSecond != NULL)
	{
		enqueue(first, last, dequeue(firstOfFirst, lastOfFirst));
		enqueue(first, last, dequeue(firstOfSecond, lastOfSecond));
	}
}
void lastNotInt(Elem*& first, Elem*& last)
{
	while (fmod(last->info, 1) == 0)
	{
		Elem* tmp = new Elem;
		tmp->info = last->info;
		tmp->link = first;
		first = tmp;
		Elem* tmp2 = first;
		while (tmp2->link!=last)
		{
			tmp2 = tmp2->link; // 3
		}
		delete last;
		last = tmp2;
		tmp2->link = NULL;
		cout << "Перенесено ціле число" << endl;
	}


}
void enqueue(Elem*& first, Elem*& last, Info value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	tmp->link = NULL;
	if (last != NULL)
		last->link = tmp;
	last = tmp;
	if (first == NULL)
		first = tmp;
}
Info dequeue(Elem*& first, Elem*& last)
{
	Elem* tmp = first->link;
	Info value = first->info;
	delete first;
	first = tmp;
	if (first == NULL)
		last = NULL;
	return value;
}
Info scan(Elem*& first)
{
	Elem* tmp = first->link;
	Info value = first->info;
	first = tmp;
	return value;
}