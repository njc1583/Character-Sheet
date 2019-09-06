#include "algorithm-utils.h"

AlgorithmUtils::AlgorithmUtils()
{

}

// Source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> AlgorithmUtils::Split(const std::string &s, char delim) {
	std::vector<std::string> result;

	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

bool AlgorithmUtils::SToBool(const std::string &s) {
	std::regex bool_eval_regex(".*(yes|true).*", std::regex::icase);
	return std::regex_match(s, bool_eval_regex);
}

std::string AlgorithmUtils::VecToString(const std::vector<std::string> &vec, std::string delim) {
	std::string retur_str;

	for (int idx = 0; idx < vec.size(); idx++) {
		retur_str += vec[idx];

		if (idx != vec.size() - 1) {
			retur_str += delim;
		}
	}

	return retur_str;
}