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
		{"status", Command(status, subcommandCompletions(statusCommands))},
		{"project", Command(project, subcommandCompletions(projectCommands))},
		{"mess", Command(mess, subcommandCompletions(messCommands))},
		{"action", Command(action, subcommandCompletions(actionCommands))},
		{"habit", Command(habit, subcommandCompletions(habitCommands))},
		{"event", Command(event, subcommandCompletions(eventCommands))},
		{"annual", Command(annual, subcommandCompletions(annualCommands))},
		{"dep", Command(dep, subcommandCompletions(depCommands))},
		{"all", Command(all, subcommandCompletions(allCommands))},
		{"down", Command(down, projectCompletions(noCompletions))},
		{"up", Command(up, noCompletions)},
		{"top", Command(top, noCompletions)},
	};

}
#endif
