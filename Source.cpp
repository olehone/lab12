#include <iostream>
#include <Windows.h>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* link;
	Info info;
};
void enqueue(Elem*& first, Elem*& last, Info value);
Info dequeue(Elem*& first, Elem*& last);
bool Division(int value, Elem* first);
Info scan(Elem*& first);
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Elem* first = NULL,
		* last = NULL;
	Elem* firstOfDivisors = NULL,
		* lastOfDivisors = NULL;
	// створенн€ черги
	int numOfDivisors, divisor, n;
	cout << "як багато множник≥в?" << endl;
	cin >> numOfDivisors;
	cout << "—к≥льки чисел шукати?" << endl;
	cin >> n;
	for (int i = 1; i <= numOfDivisors; i++)
	{
		do
		{
			cout << "Ќатуральне значенн€(б≥льше 1) д≥льника " << i << " ?" << endl;
			cin >> divisor;
		} while (divisor <= 1);
		enqueue(firstOfDivisors, lastOfDivisors, divisor);
	}
	int z = 1;
	for (int i = 1; z <= n; i++)
	{
		if (Division(i, firstOfDivisors))
		{
			enqueue(first, last, i);
			z++;
		}
	}
	// вилученн€ та вив≥д елемент≥в
	while (first != NULL)
		cout << dequeue(first, last) << " ";
	cout << endl;
	return 0;
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
Info dequeue(Elem * &first, Elem * &last)
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
bool Division(int value, Elem * first)
{
	if (value == 1)
	{
		bool isDivisor = 0;
		Elem* tmp = first;
		while (tmp != NULL)
		{
			int x = scan(tmp);
			if (x == 1)
			{
				return true;
			}

		}
		return false;
	}
	while (value != 1)
	{
		bool isDivisor = 0;
		Elem* tmp = first;
		while (tmp != NULL)
		{
			int x = scan(tmp);
			if (value % x == 0)
			{
				value /= x;
				isDivisor = 1;
				break;
			}

		}
		if (!isDivisor)
			break;
	}
	if (value == 1)
		return true;
	else
		return false;
}