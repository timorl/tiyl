#ifndef TIYL_CLI_ACTION_HPP
#define TIYL_CLI_ACTION_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
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

	const std::map<std::string, Command> actionCommands = {
		{"list", actionList},
		{"show", actionShow},
		{"add", actionAdd},
		{"del", actionDone},
		{"done", actionDone},
	};

}
#endif
