#include "pch.h"
#include "CppUnitTest.h"
#include "..\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string five = "5", four = "4";
			bool first = false, second = false;
			Node* root = new Node;
			Node* left = new Node;
			Node* right = new Node;
			Info fiveInfo = "5";
			root->info = "5";
			left->info = "3";
			right->info = "8";
			left->left = NULL;
			left->right = NULL;
			right->left = NULL;
			right->right = NULL;
			root->left = left;
			root->right = right;
			Assert::AreEqual(2, Height(root));	
			isFind(root, five, first);
			isFind(root, four, second);
			Assert::IsTrue(first);
			Assert::IsFalse(second);
		}
	};
}
