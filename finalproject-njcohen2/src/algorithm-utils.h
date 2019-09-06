#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <regex>

// The purpose of this class is to provide non-specific static algorithms
// Boost has many of these algorithms, but this size of project
class AlgorithmUtils
{
public:
	AlgorithmUtils();

	// Source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	static std::vector<std::string> Split(const std::string &s, char delim);
	static bool SToBool(const std::string &s);
	static std::string VecToString(const std::vector<std::string> &vec, std::string delim = " ");
};

