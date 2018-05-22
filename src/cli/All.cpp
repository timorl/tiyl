#include"cli/All.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
#include"cli/Utils.hpp"
#include"cli/Mess.hpp"
#include"cli/Action.hpp"

namespace cli {

	std::function<void(Annuals &, Subproject const &)> accumulateSoonAnnualsCreator(int soon) {
		std::function<void(Annuals &, Subproject const &)> accumulateSoonAnnuals =
			[soon, &accumulateSoonAnnuals](Annuals & a, Subproject const & sp) {
				Annuals const & localAnnuals = sp.second.getAnnuals();
				for (Annual const & annual : localAnnuals) {
					if (annual.second.daysLeft() < soon) {
						a.insert(annual);
					}
				}
				sp.second.accumulateFromSubprojects(a, accumulateSoonAnnuals);
			};
		return accumulateSoonAnnuals;
	}

	const std::map<std::string, std::function<projects::AnnualAccumulator(Arguments const &)>> annualAccumulator = {
		{"", [](Arguments const &)->projects::AnnualAccumulator{return projects::accumulateAnnuals;}},
		{"within", [](Arguments const & args)->projects::AnnualAccumulator{
				Arguments newArgs = args;
				int days = requestInt("How many days", newArgs, 21);
				return accumulateSoonAnnualsCreator(days);
			}
		},
		{"soon", [](Arguments const &)->projects::AnnualAccumulator{return accumulateSoonAnnualsCreator(21);}},
	};

	int allAnnual(Context & c, Arguments const & args) {
		Annuals annuals;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(annuals, annualAccumulator.at(condition)(args));
		printAnnualNames(annuals);
		return 0;
	}

	std::function<void(Events &, Subproject const &)> accumulateSoonEventsCreator(int soon) {
		std::function<void(Events &, Subproject const &)> accumulateSoonEvents =
			[soon, &accumulateSoonEvents](Events & e, Subproject const & sp) {
				Events const & localEvents = sp.second.getEvents();
				for (Event const & event : localEvents) {
					if (event.second.daysLeft() < soon) {
						e.insert(event);
					}
				}
				sp.second.accumulateFromSubprojects(e, accumulateSoonEvents);
			};
		return accumulateSoonEvents;
	}

	const std::map<std::string, std::function<projects::EventAccumulator(Arguments const &)>> eventAccumulator = {
		{"", [](Arguments const &)->projects::EventAccumulator{return projects::accumulateEvents;}},
		{"within", [](Arguments const & args)->projects::EventAccumulator{
				Arguments newArgs = args;
				int days = requestInt("How many days", newArgs, 21);
				return accumulateSoonEventsCreator(days);
			}
		},
		{"soon", [](Arguments const &)->projects::EventAccumulator{return accumulateSoonEventsCreator(21);}},
	};

	int allEvent(Context & c, Arguments const & args) {
		Events events;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(events, eventAccumulator.at(condition)(newArgs));
		printEventNames(events);
		return 0;
	}

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
		sp.second.accumulateFromSubprojects(h, accumulatePastHabits);
	}

	const std::map<std::string, projects::HabitAccumulator> habitAccumulator = {
		{"", projects::accumulateHabits},
		{"due", accumulateDueHabits},
		{"past", accumulatePastHabits},
	};

	int allHabit(Context & c, Arguments const & args) {
		Habits habits;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(habits, habitAccumulator.at(condition));
		printHabitNames(habits);
		return 0;
	}

	void accumulateDoableActions(Actions & a, Subproject const & sp) {
		Actions const & localActions = sp.second.getActions();
		for (Action const & action : localActions) {
			if (action.second.getDependencies().empty()) {
				a.insert(action);
			}
		}
		sp.second.accumulateFromSubprojects(a, accumulateDoableActions);
	}

	const std::map<std::string, projects::ActionAccumulator> actionAccumulator = {
		{"", projects::accumulateActions},
		{"doable", accumulateDoableActions},
	};

	int allAction(Context & c, Arguments const & args) {
		Actions actions;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(actions, actionAccumulator.at(condition));
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

	const Commands allCommands = {
		{"mess", Command(allMess, noCompletions)},
		{"action", Command(allAction, nameCompletions(keyVector(actionAccumulator), noCompletions))},
		{"habit", Command(allHabit, nameCompletions(keyVector(habitAccumulator), noCompletions))},
		{"event", Command(allEvent, nameCompletions(keyVector(eventAccumulator), noCompletions))},
		{"annual", Command(allAnnual, nameCompletions(keyVector(annualAccumulator), noCompletions))},
	};

}
