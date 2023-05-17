#include <iostream>
using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};
void PrintTree(Node* root, int level);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
Node* Find(Node* root, Info value);
Node* FindMax(Node* root);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
int Height(Node* root);
int BFactor(Node* root);
void BalanceHeight(Node*& root);
Node* BinarySearchDelete(Node* root, Info val);
void DeleteTree(Node*& root, Node* node);
int Count(Node* root);
void printMenu() {
	cout << "\nChoose an action:\n";
	cout << "1. Create a binary tree\n";
	cout << "2. Display the binary tree\n";
	cout << "3. Add a new element maintaining order\n";
	cout << "4. Balance the binary search tree\n";
	cout << "5. Remove a tree element with no child nodes\n";
	cout << "6. Remove a tree element with one child node\n";
	cout << "7. Remove a tree element with two child nodes\n";
	cout << "8. Remove a tree element with all its child nodes\n";
	cout << "9. Determine the number of tree elements\n";
}
int main()
{
	int N;
	int choice;
	Node* root = NULL;
	Info value;
	bool found = false;
	while (true) {
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Nodes count: "; cin >> N;

			for (int i = 0; i < N; i++)
			{
				cout << "value: "; cin >> value;
				BinarySearchInsert(root, value, found);
			}
			cout << endl;
			break;
		}
		case 2:
		{
			PrintTree(root, 0);
			cout << endl;
			break;
		}
		case 3:
		{
			int value;
			cout << "Enter the value: ";
			cin >> value;
			BinarySearchInsert(root, value, found);
			break;
		}
		case 4:
		{
			BalanceHeight(root);
			std::cout << "Binary search tree balanced.\n";
			break;
		}
		case 5:
		case 6:
		case 7:
		{
			int value;
			cout << "Enter the value: ";
			cin >> value;
			BinarySearchDelete(root, value);
			break;
		}
		case 8: 
		{
			int value;
			cout << "Enter the value: ";
			cin >> value;
			DeleteTree(root, Find(root, value));
			break;
		}
		case 9: 
		{
			cout << "Count: " << Count(root)<<endl;
			break;
		}
		default:
			cout << "Incorrect choice, try again.\n";
		}
	}
	cout << endl;
	PrintTree(root, 0);
	cout << endl;
	return 0;
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
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}
int Count(Node* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + Count(root->left) + Count(root->right);
}
Node* Find(Node* root, Info value)
{
	if (root == NULL || value == root->info)
		return root;
	if (value < root->info)
		return Find(root->left, value);
	else
		return Find(root->right, value);
}
Node* FindMax(Node* root)
{
	if (root
		->right != NULL
		)
		return FindMax(root
			->right);
	else
		return root;
}
void RightRotation(Node*& root) {
	Node* tmp1 = root
		->left;
	Node* tmp2 = tmp1
		->right;
	tmp1
		->right = root;
	root
		->left = tmp2;
	root = tmp1;
}
void LeftRotation(Node*& root) {
	Node* tmp1 = root
		->right;
	Node* tmp2 = tmp1
		->left;
	tmp1
		->left = root;
	root
		->right = tmp2;
	root = tmp1;
}
int Height(Node* root) {
	if (root == NULL
		)
		return 0;

	int hL = Height(root
		->left);
	int hR = Height(root
		->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root) {
	return Height(root
		->right)
		- Height(root
			->left);
}
void BalanceHeight(Node*& root) {
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <=
			-2)

		{
			if (BFactor(root
				->left) > 0)
				LeftRotation(root
					->left);
			RightRotation(root);

		}
		BalanceHeight(root
			->left);
		BalanceHeight(root
			->right);

	}
}
Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL;
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right)
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}
void DeleteTree(Node*& root, Node* node)
{
	if (node != NULL)
	{
		DeleteTree(root, node->left);
		DeleteTree(root, node->right);
		root = BinarySearchDelete(root, node->info);
	}
}