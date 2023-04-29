#include <iostream>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <iomanip>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* next;
	Elem* prev;
	Info info;
};
//��������� �������� � �����'����� ������
void enqueue(Elem*& L, Info value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	//���� ���� ��������
	if (L == NULL)
	{
		L = tmp;
		L->prev = L;
		L->next = L;
		return;
	}
	//���� ���� �������
	if (L->prev == L)
	{
		L->prev = tmp;
		L->next = tmp;
		tmp->prev = L;
		tmp->next = L;
		return;
	}
	//���� ����� ��������
	Elem* prevL = L->prev;
	L->prev = tmp;
	tmp->next = L;
	prevL->next = tmp;
	tmp->prev = prevL;
}
void Print(Elem* L)
{
	//���� ���� ��������
	if (L == NULL)
		return;
	//���� ������� ����
	if (L->next == L)
	{
		cout << setw(4) << L->info << endl;
		return;
	}
	//���� ����� ��������
	Elem* L2 = L;
	do
	{
		cout << setw(4) << L2->info;
		L2 = L2->next;
	} while (L2 != L);
	cout << endl;
}
Elem* sameNext(Elem* L)
{
	Elem* values = NULL;
	//���� ���� ��������
	if (L == NULL)
		return NULL;
	//���� ������� ����
	if (L->next == L)
		return NULL;
	//���� ����� ��������
	Elem* L2 = L;
	do
	{
		if (L2->info == L2->next->info)
			enqueue(values, L2->info);
		L2 = L2->next;
	} while (L2 != L);
	return values;
}
bool RemovalByNeighbors(Elem*& L)
{
	Elem* L2 = L;
	bool isRemov = false;
	bool itsRemov = false;
	do
	{
		itsRemov = false;
		do
		{
			if (L2 == NULL || L2->next == L2 || L2->next == L2->prev)
				continue;
			if (L->next->info == L->prev->info)
			{
				Elem* tmp = L->next;
				L->prev->next = L->next;
				L->next->prev = L->prev;
				delete L;
				L = tmp;
				itsRemov = true;
				L2 = L->next;
			}
			else if (L2->next->info == L2->prev->info)
			{
				Elem* tmp = L2->next;
				L2->prev->next = L2->next;
				L2->next->prev = L2->prev;
				delete L2;
				L2 = tmp;
				itsRemov = true;
			}
			if (itsRemov)
				isRemov = true;
			L2 = L2->next;
		} while (L2 != L);
	} while (itsRemov);
	return isRemov;
}
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	Elem* L = NULL;
	ifstream inputFile("input.txt");
	int value;
	while (inputFile >> value) {
		// ��������� �������� �� ������
		enqueue(L,value);
	}
	inputFile.close();
	Print(L);
	Elem* ner = sameNext(L);
	if (ner != NULL)
	{
		cout << "��������, �� ��������� ��������, �� ��� �� ���� �� �����: ";
		Print(ner);
	}
	else cout << "���� ��������, �� ��������� ��������, �� ��� �� ���� �� �����" << endl;
	if (RemovalByNeighbors(L))
	{
		cout << "�������� �������� � ����������� �������, ����� ������: ";
		Print(L);
	}
	else
		cout << "���� �������� � ���������� �������: ";
	return 0;
}
