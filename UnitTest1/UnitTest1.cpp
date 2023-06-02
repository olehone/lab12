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
			Elem* L = NULL;
			L = loadFromFile("C:/Users/Олег/Desktop/ПКР/Індивідуальні лаби/12.11/laba12.1/UnitTest1/test2.txt");
			Assert::AreNotEqual(L->info.flightNumber, 1112);
			bubbleSortByFlightNumber(L);
			Assert::AreEqual(L->info.flightNumber, 1112);
		}
	};
}
