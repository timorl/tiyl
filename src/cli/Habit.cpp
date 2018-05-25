#include"cli/Habit.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
#include"cli/Utils.hpp"

namespace cli {

	using HabitDetails = projects::HabitDetails;

	void printHabit(Habit const & h) {
		std::cout << "Name: " << h.first << std::endl;
		HabitDetails const & details = h.second;
		std::cout << "Last done: " << util::dateToString(details.getLastDone()) << std::endl;
		std::cout << "Minimal break: " << details.getMinBreak() << std::endl;
		std::cout << "Maximal break: " << details.getMaxBreak() << std::endl;
	}

	void printHabitShort(Habit const & h) {
		std::string toPrint = h.first;
		HabitDetails const & habit = h.second;
		if (habit.pastDue()) {
			toPrint = red(toPrint);
		} else if (!habit.due()) {
			toPrint = lessVisible(toPrint);
		}
		std::cout << toPrint << std::endl;
	}

	void printHabitNames(Habits const & habits) {
		if (habits.empty()) {
			std::cout << lessVisible("No habits.") << std::endl;
			return;
		}
		std::cout << brightWhite("Habits:") << std::endl;
		for (Habit const & a : habits) {
			std::cout << " ";
			printHabitShort(a);
		}
	}

	int habitDone(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Habits const & habits = c.getProject().getHabits();
		if (habits.empty()) {
			std::cout << "No habits." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(habits), a, "habit");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		c.doHabit(name);
		c.moveUp(path);
		return 0;
	}

	Habit buildHabit(Arguments const & args) {
		Arguments a = args;
		std::string name = requestString("Name", a);
		int minimalBreak = requestInt("Minimal break", a, 1);
		int maximalBreak = requestInt("Maximal break", a, 2);
		return Habit(std::move(name), HabitDetails(minimalBreak, maximalBreak, util::now()));
	}

	int habitAdd(Context & c, Arguments const & args) {
		if ( !c.addHabit( buildHabit(args) ) ) {
			std::cout << "Habit name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int habitDel(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Habits const & habits = c.getProject().getHabits();
		if (habits.empty()) {
			std::cout << "No habits." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(habits), a, "habit");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		c.delHabit(name);
		c.moveUp(path);
		return 0;
	}

	int habitList(Context & c, Arguments const &) {
		Habits const & habits = c.getProject().getHabits();
		printHabitNames(habits);
		return 0;
	}

	int habitShow(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Habits const & habits = c.getProject().getHabits();
		if (habits.empty()) {
			std::cout << "No habits." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(habits), a, "habit");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		printHabit(Habit(name, habits.at(name)));
		c.moveUp(path);
		return 0;
	}

	int habit(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(habitCommands, c, subcommand, newArgs);
	}

	const Commands habitCommands = {
		{"list", Command(habitList, noCompletions)},
		{"show", Command(habitShow, habitCompletions(noCompletions))},
		{"add", Command(habitAdd, noCompletions)},
		{"del", Command(habitDel, habitCompletions(noCompletions))},
		{"done", Command(habitDone, habitCompletions(noCompletions))},
	};

}
