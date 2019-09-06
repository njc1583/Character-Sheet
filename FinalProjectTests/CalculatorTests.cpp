#include "stdafx.h"
#include "CppUnitTest.h"
#include "../finalproject-njcohen2/src/dnd-calculator.h"
#include "../finalproject-njcohen2/src/dnd-calculator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalProjectTests
{		
	TEST_CLASS(CalculatorTest) {

	public:
		DNDCalculator calculator;
		std::string valid = "VALID";
		std::string number_space_error = "Error: numbers cannot have spaces within them.";
		std::string multi_operator_error = "Error: back-to-back operators.";

		// BASIC EQUATIONS

		TEST_METHOD(TestBasicEquations1) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("46+556"));
			Assert::AreEqual(std::string("46 556 +"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("602"), calculator.EvaluatePostFix());
		}

		TEST_METHOD(TestBasicEquations2) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("46*98"));
			Assert::AreEqual(std::string("46 98 *"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("4508"), calculator.EvaluatePostFix());
		}

		TEST_METHOD(TestBasicEquations3) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("23+24-90*80/100"));
			Assert::AreEqual(std::string("23 24 + 90 80 * 100 / -"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("-25"), calculator.EvaluatePostFix());
		}

		TEST_METHOD(TestBasicEquations4) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("5D10-200"));
			Assert::AreEqual(std::string("5 10 D 200 -"), calculator.GetPostFixString());
		}

		TEST_METHOD(TestBasicEquations5) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("5D10H9+5D4L2"));
			Assert::AreEqual(std::string("5 10 D 9 H 5 4 D 2 L +"), calculator.GetPostFixString());
		}
	
		TEST_METHOD(TestBasicEqustions6) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("10+-60"));
			Assert::AreEqual(std::string("10 -60 +"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("-50"), calculator.EvaluatePostFix());
		}

		// STRANGE INPUTS

		TEST_METHOD(TestStrangeInputs1) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("2-6+45 * 89"));
			Assert::AreEqual(std::string("2 6 - 45 89 * +"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("4001"), calculator.EvaluatePostFix());
		}

		TEST_METHOD(TestStrangeInputs2) {
			Assert::AreEqual(valid, calculator.GeneratePostFix(" 5 d 10 h 2 + 10 d 100"));
			Assert::AreEqual(std::string("5 10 D 2 H 10 100 D +"), calculator.GetPostFixString());
		}

		TEST_METHOD(TestStrangeInputs3) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("1020 d 80 + 8d5 - 5d7l2"));
			Assert::AreEqual(std::string("1020 80 D 8 5 D + 5 7 D 2 L -"), calculator.GetPostFixString());
		}

		TEST_METHOD(TestStrangeInputs4) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("10     +     20"));
			Assert::AreEqual(std::string("10 20 +"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("30"), calculator.EvaluatePostFix());
		}

		TEST_METHOD(TestStrangeInputs5) {
			Assert::AreEqual(valid, calculator.GeneratePostFix("10 x 20"));
			Assert::AreEqual(std::string("10 20 X"), calculator.GetPostFixString());
			Assert::AreEqual(std::string("200"), calculator.EvaluatePostFix());
		}

		// ERRORS

		TEST_METHOD(TestInvalidOperators) {
			Assert::AreEqual(std::string("Error: ( operator not supported."), calculator.GeneratePostFix("25+63+(90-100)"));
			Assert::AreEqual(std::string("Error: K operator not supported."), calculator.GeneratePostFix("25D10K15"));
		}

		TEST_METHOD(TestInvalidNumbers) {
			Assert::AreEqual(number_space_error, calculator.GeneratePostFix("10 + 2 0 - 40"));
			Assert::AreEqual(number_space_error, calculator.GeneratePostFix("1 0 + 20 - 40"));
			Assert::AreEqual(number_space_error, calculator.GeneratePostFix("10 + 20 - 4 0"));
		}

		TEST_METHOD(TestBackToBackOPerators) {
			Assert::AreEqual(multi_operator_error, calculator.GeneratePostFix("10 + 20 * 30 / * 40"));
			Assert::AreEqual(multi_operator_error, calculator.GeneratePostFix("20 D 10 + 5 D 10 L 30 + 20 DL 10"));
		}

		TEST_METHOD(TestBadStartOfExpression) {
			Assert::AreEqual(std::string("Error: expression does not start with operand."), calculator.GeneratePostFix("+20"));
		}

		TEST_METHOD(TestBadEndingExpressions) {
			Assert::AreEqual(std::string("Error: expression does not end with operand."), calculator.GeneratePostFix("10 + 20 *"));
		}

	};
}