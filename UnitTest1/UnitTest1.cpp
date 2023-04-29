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
			Elem* first = NULL,
				* last = NULL;
			Elem* firstOfSecond = NULL,
				* lastOfSecond = NULL;
			Elem* firstOfFirst = NULL,
				* lastOfFirst = NULL;
			for (int i = 1; i <= 2; i++)
			{
				enqueue(firstOfFirst, lastOfFirst, i);
			}
			for (int i = 1; i <= 2; i++)
			{
				enqueue(firstOfSecond, lastOfSecond, i);
			}
			mixQueue(firstOfFirst, firstOfSecond, lastOfFirst, lastOfSecond, first, last);
			Assert::AreEqual(first->link->link->info, first->link->link->link->info);
		}
	};
}
