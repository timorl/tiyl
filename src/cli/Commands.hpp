#ifndef TIYL_CLI_COMMANDS_HPP
#define TIYL_CLI_COMMANDS_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"cli/Movement.hpp"
#include"cli/Mess.hpp"
#include"cli/Habit.hpp"
#include"cli/Action.hpp"
#include"cli/Project.hpp"
#include"cli/All.hpp"
#include"cli/Status.hpp"

namespace cli {

	const std::map<std::string, Command> commands = {
		{"status", status},
		{"project", project},
		{"mess", mess},
		{"action", action},
		{"habit", habit},
		{"all", all},
		{"down", down},
		{"up", up},
		{"top", top},
	};

}
#endif
