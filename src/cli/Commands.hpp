#ifndef TIYL_CLI_COMMANDS_HPP
#define TIYL_CLI_COMMANDS_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"cli/Todo.hpp"
#include"cli/Project.hpp"

namespace cli {

	int status(Context & c, std::vector<std::string> const &);

	int down(Context & c, std::vector<std::string> const & args);

	int up(Context & c, std::vector<std::string> const &);

	int top(Context & c, std::vector<std::string> const &);

	const std::map<std::string, Command> commands = {
		{"status", status},
		{"project", project},
		{"todo", todo},
		{"down", down},
		{"up", up},
		{"top", top},
	};

}
#endif
