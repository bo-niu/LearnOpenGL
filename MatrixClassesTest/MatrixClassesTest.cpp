#include "pch.h"
#include "CppUnitTest.h"
#include "../LearnOpenGL/BoMath/BoMatrix.h"
#include "../LearnOpenGL/BoMath/BoQuaternion.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixClassesTest
{
	TEST_CLASS(MatrixClassesTest)
	{
	public:
		int a = 100;
		TEST_METHOD(TestMethod1)
		{
			a++;
			Assert::AreEqual(a, 101);
		}

		TEST_METHOD(TestMethod2)
		{
			a++;
			Assert::AreEqual(a, 101);
		}
	};
}
