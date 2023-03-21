#include <iostream>
#include <iomanip>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* next,
		* prev;
	Info info;
};
void enqueue(Elem*& first, Elem*& last, Info value);
void print(Elem* L);
bool dequeue(Elem*& first, Elem* last, Info value);
int main()
{
	Elem* first = NULL,
		* last = NULL;
	int numberElements = 0;
	cout << "How many queue elements?(>=1): ";
	do
	{
		cin >> numberElements;
	} while (numberElements < 1);
	// ��������� �����
	Info value;
	for (int i = 1; i <= numberElements; i++)
	{
		cout << " Value of " << i << " element: ";
		cin >> value;
		enqueue(first, last, value);
	}
	// ���� ��������
	print(first);
	// �������� �������� �������� �� ��������� �����������
	// �������� � ����� ���������
	cout << "Search value? ";
	cin >> value;
	if (dequeue(first, last, value))
	{
		cout << "Delete elements, new queque: " << endl;
		print(first);
	}
	else cout << "Nothing to delete";
	cout << endl;
	return 0;
}
// ������� ��������� ��������, �� ������ ��������
// � ����� �������� info �������� � ��������� value
bool dequeue(Elem*& first, Elem* last, Info value)
{
	//���� �������� 0 ��� 1, �� �� ����������
	if (first == last)
		return false;
	//������� ������ �� ������� ��������
	Elem* L = first->next; // 1
	while (L != NULL)
	{
		if (L->info==value) //���� ����� ���������
		{
			if (first == L->prev) //���� � ���� ��� ��������
			{
				delete first;
				first = L;
			}
			else
			{
				//�������� �� ������� �� ��������� ��� ����, ���� ����������
				Elem* tmp = L->prev->prev; // 3
				delete L->prev; // 4
				L->prev = tmp;  // 5
				tmp->next = L;  // 6
			}
		}
		L = L->next; // 2
	}
	return true;
}

void print(Elem* L)
{
	if (L == NULL)
		return;
	Elem* first = L;
	cout << setw(4) << L->info;
	while (L->next != NULL)
	{
		L = L->next;
		cout << setw(4) << L->info;
	}
	cout << endl;
}
void enqueue(Elem*& first, Elem*& last, Info value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	tmp->next = NULL;
	if (last != NULL)
		last->next = tmp;
	tmp->prev = last;
	last = tmp;
	if (first == NULL)
		first = tmp;
}