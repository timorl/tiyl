#include"cli/Tokenizing.hpp"

namespace cli {

	std::string getSingleToken(std::string const & input, unsigned long long & start) {
		while (start < input.length() && input[start] == ' ') {
			start++;
		}
		if (start >= input.length()) {
			return "";
		}
		std::string result;
		unsigned long long end;
		if (input[start] == '"') {
			start++;
			if (start >= input.length()) {
				return "";
			}
			end = input.find('"', start);
			if (end == std::string::npos) {
				end = input.length()-1;
			}
		} else {
			end = input.find(' ', start);
			if (end == std::string::npos) {
				end = input.length();
			}
		}
		result = input.substr(start, end - start);
		start = end+1;
		return result;
	}

	Arguments tokenize(std::string const & input) {
		Arguments result;
		unsigned long long position = 0;
		while (position < input.length()) {
			std::string token = getSingleToken(input, position);
			if (token.length() != 0) {
				result.push_back(token);
			}
		}
		return result;
	}

}
