#include "pch.h"
#include "CppUnitTest.h"
#include "..\\Source.cpp"

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
			Elem* firstOfDivisors = NULL,
				* lastOfDivisors = NULL;
			enqueue(firstOfDivisors, lastOfDivisors, 2);
			enqueue(firstOfDivisors, lastOfDivisors, 3);
			enqueue(firstOfDivisors, lastOfDivisors, 5);
			int z = 1;
			for (int i = 1; z <= 5; i++)
			{
				if (Division(i, firstOfDivisors))
				{
					enqueue(first, last, i);
					z++;
				}
			}
			Assert::AreEqual(6, last->info);
			
		}
	};
}
