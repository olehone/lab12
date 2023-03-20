#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"
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
			Assert::AreEqual(calculateSum(first), 12);
		}
	};
}
