#ifndef TIYL_CLI_MOVEMENT_HPP
#define TIYL_CLI_MOVEMENT_HPP
#include<string>
#include<vector>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int down(Context & c, Arguments const & args);

	int up(Context & c, Arguments const &);

	int top(Context & c, Arguments const &);

}
#endif
