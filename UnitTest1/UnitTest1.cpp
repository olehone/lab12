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
			Elem* top = NULL;
			Elem* reversTop = NULL;
			Elem* testTop = NULL;
			for(int i = 1; i < 6; i++)
				Push(top, i);
			Reverse(top, reversTop);
			for(int i = 5; i > 0; i--)
				Push(testTop, i);
			Elem* tTestTop = testTop;
			Elem* tReversTop = reversTop;
			while (tTestTop != NULL || tReversTop != NULL)
			{
				Assert::AreEqual(tReversTop->info, tTestTop->info);
				tTestTop = tTestTop->link;
				tReversTop = tReversTop->link;
			}
		}
	};
}
