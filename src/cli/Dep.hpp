#ifndef TIYL_CLI_DEP_HPP
#define TIYL_CLI_DEP_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int depAdd(Context & c, Arguments const & args);

	int dep(Context & c, Arguments const & args);

	const std::map<std::string, Command> depCommands = {
		{"add", depAdd},
	};

}
#endif
