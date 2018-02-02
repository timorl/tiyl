#ifndef TIYL_CLI_PROJECT_HPP
#define TIYL_CLI_PROJECT_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	int projectShow(Context & c, Arguments const &);

	int projectFreeze(Context & c, Arguments const &);

	int projectThaw(Context & c, Arguments const &);

	int projectDelete(Context & c, Arguments const & args);

	int projectCreate(Context & c, Arguments const & args);

	int project(Context & c, Arguments const & args);

	const std::map<std::string, Command> projectCommands = {
		{"show", projectShow},
		{"freeze", projectFreeze},
		{"thaw", projectThaw},
		{"delete", projectDelete},
		{"create", projectCreate},
	};

}
#endif
