#include"cli/All.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
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

	std::function<void(Annuals &, Subproject const &)> annualAccumulator(Arguments const & args) {
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		if (condition.empty()) {
			return projects::accumulateAnnuals;
		}
		if (condition == "within") {
			int days = requestInt("How many days", newArgs, 21);
			return accumulateSoonAnnualsCreator(days);
		}
		if (condition == "soon") {
			return accumulateSoonAnnualsCreator(21);
		}
		return projects::accumulateAnnuals;
	}

	int allAnnual(Context & c, Arguments const & args) {
		Annuals annuals;
		c.getProject().accumulateFromSubprojects(annuals, annualAccumulator(args));
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

	std::function<void(Events &, Subproject const &)> eventAccumulator(Arguments const & args) {
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		if (condition.empty()) {
			return projects::accumulateEvents;
		}
		if (condition == "within") {
			int days = requestInt("How many days", newArgs, 21);
			return accumulateSoonEventsCreator(days);
		}
		if (condition == "soon") {
			return accumulateSoonEventsCreator(21);
		}
		return projects::accumulateEvents;
	}

	int allEvent(Context & c, Arguments const & args) {
		Events events;
		c.getProject().accumulateFromSubprojects(events, eventAccumulator(args));
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

	void accumulateDoableActions(Actions & a, Subproject const & sp) {
		Actions const & localActions = sp.second.getActions();
		for (Action const & action : localActions) {
			if (action.second.getDependencies().empty()) {
				a.insert(action);
			}
		}
		sp.second.accumulateFromSubprojects(a, accumulateDoableActions);
	}

	std::map<std::string, std::function<void(Actions &, Subproject const &)>> actionAccumulator = {
		{"", projects::accumulateActions},
		{"doable", accumulateDoableActions},
	};

	int allAction(Context & c, Arguments const & args) {
		Actions actions;
		Arguments newArgs;
		std::string condition = splitSubcommand(args, newArgs, "");
		c.getProject().accumulateFromSubprojects(actions, actionAccumulator[condition]);
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
