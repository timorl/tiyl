#ifndef TIYL_CLI_PARSING_HPP
#define TIYL_CLI_PARSING_HPP

#include<string>
#include<vector>

namespace util {

	std::vector<std::string> tokenize(std::string const & input);

	std::vector<std::string> tokenizePath(std::string const & input);

}
#endif
