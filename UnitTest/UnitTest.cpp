#include "pch.h"
#include "CppUnitTest.h"
#include "Complex.hpp" // ?????????? ?????????? "Complex.hpp" ??? ?????? ? ???????????? ???????


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace cpx;


namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto actual = (1 + Complex(5, 90, EXP) + 1.f + 1l + 1u + 1.l) * 1;
			auto expected = Complex(5, 5);

			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod2)
		{
			auto actual = Complex(1, 1) - Complex(1.41421356237, 45, EXP);
			auto expected = Complex(0);

			Assert::IsTrue(actual == expected);
		}
		
		TEST_METHOD(TestMethod3)
		{
			auto actual = Complex(25, 180, EXP) * Complex(5, 180, EXP);
			auto expected = Complex(125, 360, EXP);

			Complex::SetOutForm(OutForm::OUT_EXP);
			Logger::WriteMessage(actual.ToString().c_str());
			Logger::WriteMessage("\n");
			Logger::WriteMessage(expected.ToString().c_str());
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(TestMethod4)
		{
			auto actual = Complex(25, 180, EXP) / Complex(5, 180, EXP);
			auto expected = Complex(5, 360, EXP);

			Complex::SetOutForm(OutForm::OUT_EXP);
			Logger::WriteMessage(actual.ToString().c_str());
			Logger::WriteMessage("\n");
			Logger::WriteMessage(expected.ToString().c_str());
			Assert::IsTrue(actual == expected);
		}
	};
}
