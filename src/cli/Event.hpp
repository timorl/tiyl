#ifndef TIYL_CLI_EVENT_HPP
#define TIYL_CLI_EVENT_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"
#include"projects/Event.hpp"

namespace cli {

	using Event = projects::Event;
	using Events = projects::Events;

	void printEventNames(Events const & events);

	int eventAdd(Context & c, Arguments const & args);

	int eventDel(Context & c, Arguments const & args);

	int eventList(Context & c, Arguments const &);

	int eventShow(Context & c, Arguments const & args);

	int event(Context & c, Arguments const & args);

	extern const Commands eventCommands;

}
#endif
