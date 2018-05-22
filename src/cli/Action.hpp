#ifndef TIYL_CLI_ACTION_HPP
#define TIYL_CLI_ACTION_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"
#include"projects/Action.hpp"

namespace cli {

	using Action = projects::Action;
	using Actions = projects::Actions;

	void printActionNames(Actions const & actions);

	int actionDone(Context & c, Arguments const & args);

	int actionAdd(Context & c, Arguments const & args);

	int actionList(Context & c, Arguments const &);

	int actionShow(Context & c, Arguments const & args);

	int action(Context & c, Arguments const & args);

	const Commands actionCommands = {
		{"list", Command(actionList, noCompletions)},
		{"show", Command(actionShow, actionCompletions(noCompletions))},
		{"add", Command(actionAdd, noCompletions)},
		{"del", Command(actionDone, actionCompletions(noCompletions))},
		{"done", Command(actionDone, actionCompletions(noCompletions))},
	};

}
#endif
