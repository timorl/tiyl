#ifndef TIYL_CLI_STATUS_HPP
#define TIYL_CLI_STATUS_HPP

#include"cli/Command.hpp"

namespace cli {

	int statusLong(Context & c, Arguments const &);

	int statusShort(Context & c, Arguments const &);

	int status(Context & c, Arguments const & args);

	const Commands statusCommands = {
		{"short", Command(statusShort, noCompletions)},
		{"long", Command(statusLong, noCompletions)},
	};

}
#endif
