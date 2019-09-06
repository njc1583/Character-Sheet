#include "stdafx.h"
#include "CppUnitTest.h"
#include "../finalproject-njcohen2/src/algorithm-utils.h"
#include "../finalproject-njcohen2/src/algorithm-utils.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalProjectTests
{
	TEST_CLASS(AlgorithmUtilsTest) {

public:
	

	// BASIC EQUATIONS

	TEST_METHOD(TestBasicSplitMethod) {
		std::string nums("1 2 3 4 5 6 7 8 9 10");
		std::vector<std::string> num_vec = AlgorithmUtils::Split(nums, ' ');

		Assert::AreEqual((size_t)10, num_vec.size());

		for (int i = 0; i < num_vec.size(); i++) {
			Assert::AreEqual(num_vec[i], std::to_string(i + 1));
		}
	}

	};
}