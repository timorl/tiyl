#ifndef TIYL_CLI_ALL_HPP
#define TIYL_CLI_ALL_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"cli/Habit.hpp"

namespace cli {

	void accumulateDueHabits(Habits & h, Subproject const & sp);

	void accumulatePastHabits(Habits & h, Subproject const & sp);

	int allHabit(Context & c, Arguments const & args);

	int allAction(Context & c, Arguments const & args);

	int allMess(Context & c, Arguments const &);

	int all(Context & c, Arguments const & args);

	const std::map<std::string, Command> allCommands = {
		{"mess", allMess},
		{"action", allAction},
		{"habit", allHabit},
	};

}
#endif