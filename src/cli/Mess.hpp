#ifndef TIYL_CLI_MESS_HPP
#define TIYL_CLI_MESS_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"

namespace cli {

	void printMess(Mess const & mess);

	int messAdd(Context & c, Arguments const & args);

	int messFix(Context & c, Arguments const & args);

	int messList(Context & c, Arguments const &);

	int mess(Context & c, Arguments const & args);

	const Commands messCommands = {
		{"list", Command(messList, noCompletions)},
		{"fix", Command(messFix, noCompletions)},
		{"add", Command(messAdd, noCompletions)},
	};

}
#endif
