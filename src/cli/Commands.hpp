#ifndef TIYL_CLI_COMMANDS_HPP
#define TIYL_CLI_COMMANDS_HPP
#include<string>
#include<map>

#include"cli/Context.hpp"

namespace cli {

	using Command = std::function<int(Context &, std::vector<std::string> const &)>;

	int status(Context & c, std::vector<std::string> const &);

	const std::map<std::string, Command> commands = {
		{"status", status},
	};

}
#endif
