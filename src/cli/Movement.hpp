#ifndef TIYL_CLI_MOVEMENT_HPP
#define TIYL_CLI_MOVEMENT_HPP
#include<string>
#include<vector>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int down(Context & c, std::vector<std::string> const & args);

	int up(Context & c, std::vector<std::string> const &);

	int top(Context & c, std::vector<std::string> const &);

}
#endif
