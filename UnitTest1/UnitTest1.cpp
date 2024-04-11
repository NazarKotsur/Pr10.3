#include "pch.h"
#include "CppUnitTest.h"
#include "../Pr10.3/Pr10.3.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IsValidDouble_ValidInput_ReturnsTrue)
		{
			string validInput = "3.14";

			bool isValid = IsValidDouble(validInput);

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(IsValidDouble_InvalidInput_ReturnsFalse)
		{
			string invalidInput = "abc";

			bool isValid = IsValidDouble(invalidInput);

			Assert::IsFalse(isValid);
		}
	};
}