#ifndef TIYL_CLI_HABIT_HPP
#define TIYL_CLI_HABIT_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"projects/Habit.hpp"

namespace cli {

	using Habit = projects::Habit;
	using Habits = projects::Habits;

	void printHabitNames(Habits const & habits);

	int habitDone(Context & c, Arguments const & args);

	int habitAdd(Context & c, Arguments const & args);

	int habitDel(Context & c, Arguments const & args);

	int habitList(Context & c, Arguments const &);

	int habitShow(Context & c, Arguments const & args);

	int habit(Context & c, Arguments const & args);

	const std::map<std::string, Command> habitCommands = {
		{"list", habitList},
		{"show", habitShow},
		{"add", habitAdd},
		{"del", habitDel},
		{"done", habitDone},
	};

}
#endif
