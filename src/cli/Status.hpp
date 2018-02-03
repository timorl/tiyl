#ifndef TIYL_CLI_STATUS_HPP
#define TIYL_CLI_STATUS_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int statusLong(Context & c, Arguments const &);

	int statusShort(Context & c, Arguments const &);

	int status(Context & c, Arguments const & args);

	const std::map<std::string, Command> statusCommands = {
		{"short", statusShort},
		{"long", statusLong},
	};

}
#endif
