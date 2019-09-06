#ifndef DNDCALCULATOR_H
#define DNDCALCULATOR_H

#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stdlib.h>
#include <stdexcept>

class DNDCalculator {
private:
	std::stack<std::string> calc_stack_;
	std::map<std::string, int> operator_hierarchy_;
	std::vector<std::string> postfix_tokens_;
	std::string solution_;

public:
	DNDCalculator();
	std::string Evaluate(std::string expression);
	std::string GeneratePostFix(std::string expression);
	std::string EvaluatePostFix();

	std::vector<std::string> GetPostFix();
	std::string GetPostFixString();
};

#endif