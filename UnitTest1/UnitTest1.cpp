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
			Elem* L = NULL;
			enqueue(L, 1);
			enqueue(L, 0);
			enqueue(L, 1);
			RemovalByNeighbors(L);
			Assert::AreEqual(L->next->info, L->prev->info);
		}
	};
}
