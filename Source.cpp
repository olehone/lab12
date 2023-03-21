#include <iostream>
#include <iomanip>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* link;
	Info info;
};
void Insert(Elem*& L, Info value)
{
	Elem* tmp = new Elem; 
	tmp->info = value;
	if (L != NULL)
	{
		Elem* T = L;
		while (T->link != L)
			T = T->link;
		T->link = tmp; 
	}
	else
	{
		L = tmp;
	}
	tmp->link = L;
}
Info Remove(Elem*& L)
{
	Elem* T = L;
	while (T->link != L)
		T = T->link;
	Info value = L->info;
	if (T != L)
	{
		Elem* tmp = L->link;
		delete L;
		L = tmp;
		T->link = L;
	}
	else
	{
		delete L;
		L = NULL;
	}
	return value;
}
bool Find(Elem* first)
{
	if (first == NULL||first->link==first)
		return false;
	Elem* L = first;
	while (L->link != first)
	{
		Elem* T = L->link;
		while (T != first)
		{
			if (L->info == T->info)
				return true;
			T = T->link;
		}
		L = L->link;
	}
	return false;
}
void Print(Elem* L) {
	if (L == NULL)
		return;
	Elem* first = L;
	cout << setw(4) << L->info;
	while (L->link != first)
	{
		L = L->link;
		cout << setw(4) << L->info;
	}
	cout << endl;
}
int main()
{
	Elem* L = NULL;
	int numberElements = 0;
	Info value;
	cout << "How many queue elements?(>=1): ";
	do
	{
		cin >> numberElements;
	} while (numberElements < 1);
	// створення черги
	for (int i = 1; i <= numberElements; i++)
	{
		cout << " Value of " << i << " element: ";
		cin >> value;
		Insert(L, value);
	}
	if (Find(L))
		cout << "Has a pair with the same values" << endl;
	else
		cout << "Doesn`t contain pairs with the same values" << endl;
	Print(L);
	while (L != NULL)
		Remove(L);
	cout << endl;
	return 0;
}