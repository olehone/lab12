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
			Elem* L = new Elem;
			L->info = 2;
			L->link = new Elem;
			L->link->info = 3;
			L->link->link = new Elem;
			L->link->link->info = 2;
			L->link->link->link = L;
			Assert::IsTrue(Find(L));
		}
		TEST_METHOD(TestMethod2)
		{
			Elem* L = new Elem;
			L->info = 2;
			L->link = new Elem;
			L->link->info = 3;
			L->link->link = new Elem;
			L->link->link->info = 4;
			L->link->link->link = L;
			Assert::IsTrue(!Find(L));
		}
	};
}
