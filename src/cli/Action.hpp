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

	extern const Commands actionCommands;

}
#endif
