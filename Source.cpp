#include <iostream>
#include <iomanip>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* link;
	Info info;
};
void enqueue(Elem*& first, Elem*& last, Info value);
void print(Elem* L);
Info calculateSum(Elem* L);
int main()
{
	Elem* first = NULL,
		* last = NULL;
	int numberElements = 0;
	cout << "How many queue elements?(>1): ";
	do
	{
		cin >> numberElements;
	} while (numberElements < 1);
	// створення черги
	Info value;
	for (int i = 1; i <= numberElements; i++)
	{
		cout << " Value of " << i << " element: ";
		cin >> value;
		enqueue(first, last, value);
	}
	// вивід елементів
	print(first);
	// обрахування суми елементів списку з парними значеннями
	cout << "Sum elements: " << calculateSum(first) << endl;
	cout << endl;
	return 0;
}
// функція обрахування суми елементів списку з парними значеннями поля info
Info calculateSum(Elem* L)
{
	Info Sum = 0;
	while (L != NULL)
	{
		if(L->info%2 == 0)
			Sum += L->info;
		L = L->link;
	}
	return Sum;
}

void print(Elem* L)
{
	if (L == NULL)
		return;
	Elem* first = L;
	cout << setw(4) << L->info;
	while (L->link != NULL)
	{
		L = L->link;
		cout << setw(4) << L->info;
	}
	cout << endl;
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