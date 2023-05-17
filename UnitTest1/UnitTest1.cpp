#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = NULL;
			bool found;
			for (int i = 0; i < 15; i++)
			{
				BinarySearchInsert(root, i, found);
			}
			Assert::AreEqual(Count(root), 15);
		}
	};
}
