#include "pch.h"
#include "CppUnitTest.h"
#include "Complex.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace cpx;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto actual = Complex(10, 9) + Complex(1, 90, EXP_FORM);
			auto expected = Complex(10, 10);

			Assert::IsTrue(actual == expected);
		}
	};
}
