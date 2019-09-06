#include "dnd-calculator.h"

DNDCalculator::DNDCalculator() {
	// Rolling and keeping dice are of the utmost importance
	operator_hierarchy_["D"] = 4;
	operator_hierarchy_["H"] = 3;
	operator_hierarchy_["L"] = 3;
	operator_hierarchy_["*"] = 2;
	operator_hierarchy_["X"] = 2;
	operator_hierarchy_["/"] = 2;
	operator_hierarchy_["+"] = 1;
	operator_hierarchy_["-"] = 1;
}

std::string DNDCalculator::Evaluate(std::string expression) {
	// Check validity of expression while pushing onto stack
	// Pop from stack and evaluate running total

	std::string expression_validity = GeneratePostFix(expression);

	if (expression_validity == "VALID") {
		return EvaluatePostFix();
	} else {
		return expression_validity;
	}
}

std::string DNDCalculator::GeneratePostFix(std::string expression) {
	while (!calc_stack_.empty()) {
		calc_stack_.pop();
	}

	postfix_tokens_.clear();

	std::transform(expression.begin(), expression.end(), expression.begin(), ::toupper);

	std::string operand;
	
	for (int i = 0; i < expression.size(); i++) {
		std::string token_str = std::string(1, expression[i]);

		// Handles white space; only valid when they are not between two digits
		if (token_str == " ") {
			if (i == 0 || i == expression.size() - 1) {
				continue;
			} else if (expression[i - 1] == ' ' || expression[i + 1] == ' '){
				expression.erase(i, 1);
				i--;
				continue;
			} else if (isdigit(expression[i - 1]) && isdigit(expression[i + 1])) {
				return "Error: numbers cannot have spaces within them.";
			} else {
				continue;
			}
		}
		
		// Handles operand vs. operator logic
		if (isdigit(expression[i])) {
			std::stoi(token_str);
			operand.append(token_str);
		} else {
			if (operator_hierarchy_.find(token_str) == operator_hierarchy_.end()) {
				return "Error: " + token_str + " operator not supported.";
			} else {
				if (postfix_tokens_.empty() && operand.empty()) {
					if (token_str == "-") {
						operand.append(token_str);
						continue;
					} else {
						return "Error: expression does not start with operand.";
					}
				} else if (operand.empty()) {
					if (token_str == "-") {
						operand.append(token_str);
						continue;
					}
					else {
						return "Error: back-to-back operators.";
					}
				}

				postfix_tokens_.push_back(operand);
				operand = "";

				while (!calc_stack_.empty() && 
					operator_hierarchy_[calc_stack_.top()] >= operator_hierarchy_[token_str]) {

					postfix_tokens_.push_back(calc_stack_.top());
					calc_stack_.pop();
				}

				calc_stack_.push(token_str);
			}
		}
	}

	if (!operand.empty()) {
		postfix_tokens_.push_back(operand);
	} else {
		return "Error: expression does not end with operand.";
	}

	while (!calc_stack_.empty()) {
		postfix_tokens_.push_back(calc_stack_.top());
		calc_stack_.pop();
	}

	return "VALID";
}

std::string DNDCalculator::EvaluatePostFix() {
	bool active_dice = false;
	std::vector<int> dice_rolls;

	while (!calc_stack_.empty()) {
		calc_stack_.pop();
	}

	for (std::string token : postfix_tokens_) {
		try {
			std::stoi(token);
			calc_stack_.push(token);
		} catch (std::invalid_argument err) {
			// n D k -> n k D
			// n H k -> n k H
			// n L k -> n k L
			// Deal with the operands as they progress

			if (token == "H" || token == "L") {
				// n doesn't exist; H and L modify the list
				int k = std::stoi(calc_stack_.top());
				calc_stack_.pop();

				if (dice_rolls.size() == 0 || k >= dice_rolls.size()) {
					return "Error: improper dice rolls.";
				}

				if (token == "L") {
					std::sort(dice_rolls.begin(), dice_rolls.end());
				} else {
					std::sort(dice_rolls.begin(), dice_rolls.end(), std::greater<int>());
				}

				for (int i = 0; i < k; i++) {
					dice_rolls.pop_back();
				}
			} else {
				int k, n;

				if (!dice_rolls.empty()) {
					int sum = 0;

					for (int roll : dice_rolls) {
						sum += roll;
					}

					dice_rolls.clear();
					n = sum;
					k = std::stoi(calc_stack_.top());
					calc_stack_.pop();
				} else {
					k = std::stoi(calc_stack_.top());
					calc_stack_.pop();
					n = std::stoi(calc_stack_.top());
					calc_stack_.pop();
				}

				if (token == "D") {
					for (int i = 0; i < n; i++) {
						int roll = rand() % k + 1;

						dice_rolls.push_back(roll);
					}
				} else if (token == "+") {
					int sum = n + k;
					calc_stack_.push(std::to_string(sum));
				} else if (token == "-") {
					int diff = n - k;
					calc_stack_.push(std::to_string(diff));
				} else if (token == "*" || token == "X") {
					int prod = n * k;
					calc_stack_.push(std::to_string(prod));
				} else if (token == "/") {
					int divisor = n / k;
					calc_stack_.push(std::to_string(divisor));
				}
			}
		}
	}

	if (!dice_rolls.empty()) {
		int sum = 0;

		for (int roll : dice_rolls) {
			sum += roll;
		}

		dice_rolls.clear();
		calc_stack_.push(std::to_string(sum));
	}

	return calc_stack_.top();
}

std::vector<std::string> DNDCalculator::GetPostFix() {
	return postfix_tokens_;
}

std::string DNDCalculator::GetPostFixString() {
	std::string message;
	
	for (int i = 0; i < postfix_tokens_.size(); i++) {
		message += postfix_tokens_[i];

		if (i != postfix_tokens_.size() - 1) {
			message += " ";
		}
	}

	return message;
}