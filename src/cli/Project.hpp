#ifndef TIYL_CLI_PROJECT_HPP
#define TIYL_CLI_PROJECT_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int projectShow(Context & c, std::vector<std::string> const &);

	int project(Context & c, std::vector<std::string> const & args);

	const std::map<std::string, Command> projectCommands = {
		{"show", projectShow},
	};

}
#endif
