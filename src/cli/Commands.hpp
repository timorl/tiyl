#ifndef TIYL_CLI_COMMANDS_HPP
#define TIYL_CLI_COMMANDS_HPP

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"cli/Completions.hpp"
#include"cli/Movement.hpp"
#include"cli/Mess.hpp"
#include"cli/Annual.hpp"
#include"cli/Event.hpp"
#include"cli/Habit.hpp"
#include"cli/Action.hpp"
#include"cli/Project.hpp"
#include"cli/Dep.hpp"
#include"cli/All.hpp"
#include"cli/Status.hpp"

namespace cli {

	const Commands commands = {
		{"status", Command(status, noCompletions)},
		{"project", Command(project, noCompletions)},
		{"mess", Command(mess, noCompletions)},
		{"action", Command(action, noCompletions)},
		{"habit", Command(habit, noCompletions)},
		{"event", Command(event, noCompletions)},
		{"annual", Command(annual, noCompletions)},
		{"dep", Command(dep, noCompletions)},
		{"all", Command(all, noCompletions)},
		{"down", Command(down, noCompletions)},
		{"up", Command(up, noCompletions)},
		{"top", Command(top, noCompletions)},
	};

}
#endif
