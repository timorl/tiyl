#include"cli/All.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
#include"cli/Mess.hpp"
#include"cli/Action.hpp"
#include"cli/Habit.hpp"

namespace cli {

	void accumulateDueHabits(Habits & h, Subproject const & sp) {
		Habits const & localHabits = sp.second.getHabits();
		for (Habit const & habit : localHabits) {
			if (habit.second.due()) {
				h.insert(habit);
			}
		}
		sp.second.accumulateFromSubprojects(h, accumulateDueHabits);
	}

	void accumulatePastHabits(Habits & h, Subproject const & sp) {
		Habits const & localHabits = sp.second.getHabits();
		for (Habit const & habit : localHabits) {
			if (habit.second.pastDue()) {
				h.insert(habit);
			}
		}
		sp.second.accumulateFromSubprojects(h, accumulateDueHabits);
	}

 std::map<std::string, std::function<void(Habits &, Subproject const &)>> habitAccumulator = {
		{"", projects::accumulateHabits},
		{"due", accumulateDueHabits},
		{"past", accumulatePastHabits},
	};

	int allHabit(Context & c, Arguments const & args) {
		Habits habits;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(habits, habitAccumulator[condition]);
		printHabitNames(habits);
		return 0;
	}

	int allAction(Context & c, Arguments const &) {
		Actions actions;
		c.getProject().accumulateFromSubprojects(actions, projects::accumulateActions);
		printActionNames(actions);
		return 0;
	}

	int allMess(Context & c, Arguments const &) {
		Mess mess;
		c.getProject().accumulateFromSubprojects(mess, projects::accumulateMess);
		printMess(mess);
		return 0;
	}

	int all(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "action");
		return singleCommand(allCommands, c, subcommand, newArgs);
	}

}
