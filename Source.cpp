#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef int Info;
struct Elem
{
	Elem* link;
	Info info;
};
int PushFromFile(Elem*& top, string filename);
void PushFromConsole(Elem*& top, int N);
void PrintStack(Elem* top);
void Reverse(Elem* top, Elem*& reversTop);
void Push(Elem*& top, Info value);
int main()
{
	Elem* top = NULL;
	Elem* reversTop = NULL;
	int N;
	string filename;
	int typeInput;
	do
	{
		cout << " Use(1/2)?\n 1. Console input\n 2. Reading file" << endl;
		cin >> typeInput;
	} while (typeInput != 1 && typeInput != 2);
	switch (typeInput)
	{
	case 1:
		cout << " How many elements? ";
		cin >> N;
		PushFromConsole(top, N);
		break;
	case 2:
		cout << " Name of file or standart(0)? ";
		cin.ignore();
		getline(cin, filename);
		if (filename == "0")
			filename = "Massive.txt";
		N = PushFromFile(top, filename);
		break;
	default:
		cout << " How? " << endl;
		break;
	}
	Reverse(top, reversTop);
	std::cout << "Stack: ";
	PrintStack(top);
	cout << "Reverse stack: ";
	PrintStack(reversTop);
	return 0;
}
int PushFromFile(Elem*& top, string filename)
{
	ifstream fin(filename);
	int n = 0;
	Info value;
	while (fin>>value)
	{
		Push(top, value);
		n++;
	}
	fin.close();
	return n;
}
void PushFromConsole (Elem*& top, int N)
{
	for (int i = 1; i <= N; i++)
	{
		Info value;
		cout << " Value of " << i << " element: ";
		cin >> value;
		Push(top, value);
	}
}
void PrintStack (Elem* top) 
{
	while (top != NULL)
	{
		cout << " " << top->info;
		top= top->link;
	}
	cout << endl;
}
void Reverse(Elem* top, Elem*& reversTop)
{
	while (top != NULL)
	{
		Push(reversTop, top->info);
		top = top->link;
	}
}
void Push(Elem*& top, Info value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	tmp->link = top;
	top = tmp;
}