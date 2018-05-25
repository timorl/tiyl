#include"util/Parsing.hpp"

#include<functional>

namespace util {

	using SingleTokenFunction = std::function<std::string(std::string const &, unsigned long long &)>;

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
				end = input.length();
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

	std::vector<std::string> tokenize(std::string const & input, SingleTokenFunction singleToken) {
		std::vector<std::string> result;
		unsigned long long position = 0;
		while (position < input.length()) {
			std::string token = singleToken(input, position);
			if (!token.empty()) {
				result.push_back(token);
			}
		}
		return result;
	}

	std::vector<std::string> tokenize(std::string const & input) {
		return tokenize(input, getSingleToken);
	}

	const char pathSeparator('/');

	std::string getSinglePathToken(std::string const & input, unsigned long long & start) {
		std::string result;
		if (input[start] == pathSeparator) {
			start++;
			if (start >= input.length()) {
				return "";
			}
		}
		unsigned long long end = input.find(pathSeparator, start);
		if (end == std::string::npos) {
			end = input.length();
		}
		end++;
		result = input.substr(start, end - start);
		start = end;
		return result;
	}

	std::vector<std::string> tokenizePath(std::string const & input) {
		return tokenize(input, getSinglePathToken);
	}

	std::string gluePath(std::vector<std::string> const & path) {
		std::string result;
		for (std::string const & p : path) {
			result += p + pathSeparator;
		}
		return result;
	}

}
