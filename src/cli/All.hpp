#ifndef TIYL_CLI_ALL_HPP
#define TIYL_CLI_ALL_HPP

#include"cli/Command.hpp"
#include"cli/Habit.hpp"
#include"cli/Event.hpp"
#include"cli/Annual.hpp"

namespace cli {

	std::function<void(Annuals &, Subproject const &)> accumulateSoonAnnualsCreator(int soon);

	std::function<void(Events &, Subproject const &)> accumulateSoonEventsCreator(int soon);

	void accumulateDueHabits(Habits & h, Subproject const & sp);

	void accumulatePastHabits(Habits & h, Subproject const & sp);

	int allAnnual(Context & c, Arguments const & args);

	int allEvent(Context & c, Arguments const & args);

	int allHabit(Context & c, Arguments const & args);

	int allAction(Context & c, Arguments const & args);

	int allMess(Context & c, Arguments const &);

	int all(Context & c, Arguments const & args);

	extern const Commands allCommands;

}
#endif
