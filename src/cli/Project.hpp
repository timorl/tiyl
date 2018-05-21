#ifndef TIYL_CLI_PROJECT_HPP
#define TIYL_CLI_PROJECT_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"

namespace cli {

	int projectShow(Context & c, Arguments const &);

	int projectFreeze(Context & c, Arguments const &);

	int projectThaw(Context & c, Arguments const &);

	int projectDelete(Context & c, Arguments const & args);

	int projectCreate(Context & c, Arguments const & args);

	int project(Context & c, Arguments const & args);

	const Commands projectCommands = {
		{"show", Command(projectShow, noCompletions)},
		{"freeze", Command(projectFreeze, noCompletions)},
		{"thaw", Command(projectThaw, noCompletions)},
		{"del", Command(projectDelete, noCompletions)},
		{"add", Command(projectCreate, noCompletions)},
	};

}
#endif
