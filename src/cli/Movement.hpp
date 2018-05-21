#ifndef TIYL_CLI_MOVEMENT_HPP
#define TIYL_CLI_MOVEMENT_HPP

#include"cli/Command.hpp"

namespace cli {

	int down(Context & c, Arguments const & args);

	int up(Context & c, Arguments const &);

	int top(Context & c, Arguments const &);

}
#endif
