#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
typedef string Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};
struct Elem
{
	Elem* link;
	Node* info;
};
Node* CreateTree(int nodeCount);
void SaveToFileFromArithmetic(string data, string out);
int checkCharacter(char character);
void isFind(Node* root, string& find, bool& doIsFind);
int check(Info info);
void PrintTree(Node* root, int level);
void PrintTreeWithoutNumbers(Node* root, int level);
void SaveToFile(fstream& f, Node* root);
void LoadFromFile(fstream& f, Node*& root);
int Height(Node* root);
void Push(Elem*& top, Node* node);
Node* Pop(Elem*& top);
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Node* root = NULL;
	int op, N = 0;
	while (true)
	{
		cout << " 1 створити дерево вручну\n 2 сформувати дерево з арифметичного виразу\n 3 знайти елемент\n 4 вивести дерево \n 5 вивести перелік операцій, що відповідають послідовності виконання\n";
		cin >> op;
		switch (op)
		{
		case 1:
		{
			cout << "Скільки елементів ? ";
			cin >> N;
			root = CreateTree(N);
			break;
		}
		case 2:
		{
			SaveToFileFromArithmetic("arithmetic.txt", "data.txt");
			fstream f;
			f.open("data.txt", ios::in);
			LoadFromFile(f, root);
			f.close();
			break;
		}
		case 3:
		{
			if (root != NULL)
			{
				string find;
				bool doIsFind = false;
				cout << " Який елемент?";
				cin.ignore();
				getline(cin, find);
				cout << find;
				isFind(root, find, doIsFind);
				if (doIsFind)
					cout << "Елемент знайдено";
				else
					cout << "Елемент не знайдено";
				cout << endl;
			}
			else
				cout << "Дерево не ініціалізоване" << endl;
			break;
		}
		case 4:
		{
			if (root != NULL)
			{
				PrintTree(root, 0);
				break;
			}
			else
				cout << "Дерево не ініціалізоване" << endl;
			break;

		}
		case 5:
		{
			if (root != NULL)
			{
				int heidht = Height(root);
				cout << "Послідовність виконання:" << endl;
				for (int i = heidht - 1; i > 0; i--)
				{
					cout << i;
				}
				cout << endl;
				PrintTreeWithoutNumbers(root, 0);
			}
			else
				cout << "Дерево не ініціалізоване" << endl;
			break;
		}
		default:
		{
			cout << " Неправильний ввід\n";
			break;
		}
		}
	}
	return 0;
}
int Height(Node* root) 
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
void isFind(Node* root, string& find, bool& doIsFind)
{
	if (root == NULL)
		return;
	if (doIsFind)
		return;
	if (root->info == find)
	{
		doIsFind = true;
		return;
	}
	else
	{
		isFind(root->left, find, doIsFind);
		isFind(root->right, find, doIsFind);
	}
}
int checkCharacter(char character)
{
	if (character == '*' || character == '/' || character == '-' || character == '+') {
		return 1; // Символ - оператор
	}
	else if (isdigit(character)) {
		return 2; // Символ - число
	}
	else{
		return 0; // Символ - інше
	}
}
int check(Info info)
{
	if (info == "*" || info == "-" || info == "+" || info == "/") {
		return 1; // Символ - оператор
	}
	else if (isdigit(info[0])) {
		return 2; // Символ - число
	}
	else {
		return 0; // Символ - інше
	}
}
void SaveToFileFromArithmetic(string data, string out)
{
	fstream dataF, outF;
	outF.open(out, ios::out);
	dataF.open(data, ios::in);

	if (!dataF) 
	{
		cout << "Не вдалося відкрити файл." << endl;
		return;
	}
	string line;
	while (getline(dataF, line)) 
	{
		for (char c : line)
		{
			switch (checkCharacter(c))
			{
			case 1:
			{
				outF << c << endl;
				break;
			}
			case 2:
			{
				outF << c << endl;
				outF << "<END>" << endl;
				outF << "<END>" << endl;
				break;
			}
			default:
				break;
			}
		}
	}
	dataF.close();
	outF.close();
}
Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;
		cout << " Enter node value: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}
void PrintTreeWithoutNumbers(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTreeWithoutNumbers(root->right, level + 1);
		if (check(root->info) == 1)
		{
			for (int i = 1; i <= level; i++)
				cout << " ";
			cout << root->info << endl;
		}
		PrintTreeWithoutNumbers(root->left, level + 1);
	}
}
void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}
void SaveToFile(fstream& f, Node* root)
{
	if (root != NULL)
	{
		f << root->info << endl;
		SaveToFile(f, root->left);
		SaveToFile(f, root->right);
	}
	else
		f << "<END>" << endl;
}
void LoadFromFile(fstream& f, Node*& root)
{
	Node* newNode, * current;
	Elem* top = NULL;
	Info c;
	if (!(f >> c)) // 1
	{
		root = NULL;
		return;
	}
	current = new Node; // 2
	current->info = c;
	current->left = NULL;
	current->right = NULL;
	root = current; // 2.1

	Push(top, current); // 2.2
	do
	{
			while (f >> c && c != "<END>") // 3
			{
				newNode = new Node;
				newNode->info = c;
				newNode->left = NULL;
				newNode->right = NULL;
				current->left = newNode; // 3.1
				current = current->left; // 3.2

				Push(top, current); // 3.3
			}

		while (f >> c)
			if (c == "<END>") // 4
			{
				if (top != NULL)
					current = Pop(top); // 4.1
			}
			else
				break;
		if (f.eof()) break;
		if (top != NULL) // 5
		{
			current = Pop(top); // 5.1
			newNode = new Node;
			newNode->info = c;
			newNode->left = NULL;
			newNode->right = NULL;
			current->right = newNode; // 5.2
			current = current->right; // 5.3
			Push(top, current); // 5.4
		}
	} while (!f.eof()); // 6
}
void Push(Elem*& top, Node* node)
{
	Elem* tmp = new Elem;
	tmp->info = node;
	tmp->link = top;
	top = tmp;
}
Node* Pop(Elem*& top)
{
	Elem* tmp = top->link;
	Node* node = top->info;
	delete top;
	top = tmp;
	return node;
}