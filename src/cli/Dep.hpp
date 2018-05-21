#ifndef TIYL_CLI_DEP_HPP
#define TIYL_CLI_DEP_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"

namespace cli {

	int depAdd(Context & c, Arguments const & args);

	int dep(Context & c, Arguments const & args);

	const Commands depCommands = {
		{"add", Command(depAdd, noCompletions)},
	};

}
#endif
