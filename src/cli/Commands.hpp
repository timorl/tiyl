#ifndef TIYL_CLI_COMMANDS_HPP
#define TIYL_CLI_COMMANDS_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"cli/Movement.hpp"
#include"cli/Mess.hpp"
#include"cli/Action.hpp"
#include"cli/Project.hpp"

namespace cli {

	int status(Context & c, Arguments const &);

	const std::map<std::string, Command> commands = {
		{"status", status},
		{"project", project},
		{"mess", mess},
		{"action", action},
		{"down", down},
		{"up", up},
		{"top", top},
	};

}
#endif
