#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testlab121
{
	TEST_CLASS(testlab121)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Elem* p;
			p = new Elem;
			p->link1 = new Elem;
			p->link2 = p->link1;
			p->link1->info = 12;
			Assert::AreEqual(p->link1->info, p->link2->info);
		}
	};
}
