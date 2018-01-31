#ifndef TIYL_CLI_PROJECT_HPP
#define TIYL_CLI_PROJECT_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int projectShow(Context & c, std::vector<std::string> const &);

	int projectFreeze(Context & c, std::vector<std::string> const &);

	int projectThaw(Context & c, std::vector<std::string> const &);

	int projectDelete(Context & c, std::vector<std::string> const & args);

	int projectCreate(Context & c, std::vector<std::string> const & args);

	int project(Context & c, std::vector<std::string> const & args);

	const std::map<std::string, Command> projectCommands = {
		{"show", projectShow},
		{"freeze", projectFreeze},
		{"thaw", projectThaw},
		{"delete", projectDelete},
		{"create", projectCreate},
	};

}
#endif
