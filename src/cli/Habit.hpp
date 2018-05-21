#ifndef TIYL_CLI_HABIT_HPP
#define TIYL_CLI_HABIT_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"
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

	const Commands habitCommands = {
		{"list", Command(habitList, noCompletions)},
		{"show", Command(habitShow, noCompletions)},
		{"add", Command(habitAdd, noCompletions)},
		{"del", Command(habitDel, noCompletions)},
		{"done", Command(habitDone, noCompletions)},
	};

}
#endif
