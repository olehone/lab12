#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.3/Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Elem* first = NULL,
				* last = NULL;
			for (int i = 1; i <= 6; i++)
			{
				enqueue(first, last, i);
			}
			for (int i = 3; i <= 6; i++)
			{
				dequeue(first, last, i);
			}
			Assert::AreEqual(first->info, 1);
			Assert::AreEqual(first->next->info, 6);
		}
	};
}
