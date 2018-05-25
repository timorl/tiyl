#include"cli/Event.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
#include"cli/Utils.hpp"

namespace cli {

	using EventDetails = projects::EventDetails;

	void printEvent(Event const & e) {
		std::cout << "Name: " << e.first << std::endl;
		EventDetails const & details = e.second;
		std::cout << "When: " << util::dateToString(details.getWhen()) << std::endl;
		std::set<std::string> const & dependencies = details.getDependencies();
		if (!dependencies.empty()) {
			std::cout << "Depends on: " << std::endl;
			for (std::string const & dep : dependencies) {
				std::cout << " " << dep << std::endl;
			}
		}
	}

	void printEventShort(Event const & e) {
		std::string name = e.first;
		EventDetails const & event = e.second;
		int daysLeft = event.daysLeft();
		std::string dateToPrint = util::dateToString(event.getWhen());
		if (daysLeft < 3) {
			dateToPrint = red(dateToPrint);
		}
		if (!e.second.getDependencies().empty()) {
			name = red(name);
		}
		std::cout << name << "(" << dateToPrint << ")" << std::endl;
	}

	void printEventNames(Events const & events) {
		if (events.empty()) {
			std::cout << lessVisible("No events.") << std::endl;
			return;
		}
		std::cout << brightWhite("Events:") << std::endl;
		for (Event const & a : events) {
			std::cout << " ";
			printEventShort(a);
		}
	}

	Event buildEvent(Arguments const & args) {
		Arguments a = args;
		std::string name = requestString("Name", a);
		Date when = requestDate("Date", a);
		return Event(std::move(name), EventDetails(when));
	}

	int eventAdd(Context & c, Arguments const & args) {
		if ( !c.addEvent( buildEvent(args) ) ) {
			std::cout << "Event name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int eventDel(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Events const & events = c.getProject().getEvents();
		if (events.empty()) {
			std::cout << "No events." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(events), a, "event");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		c.delEvent(name);
		c.moveUp(path);
		return 0;
	}

	int eventList(Context & c, Arguments const &) {
		Events const & events = c.getProject().getEvents();
		printEventNames(events);
		return 0;
	}

	int eventShow(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Events const & events = c.getProject().getEvents();
		if (events.empty()) {
			std::cout << "No events." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(events), a, "event");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		printEvent(Event(name, events.at(name)));
		c.moveUp(path);
		return 0;
	}

	int event(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(eventCommands, c, subcommand, newArgs);
	}

	const Commands eventCommands = {
		{"list", Command(eventList, noCompletions)},
		{"show", Command(eventShow, eventCompletions(noCompletions))},
		{"add", Command(eventAdd, noCompletions)},
		{"del", Command(eventDel, eventCompletions(noCompletions))},
		{"done", Command(eventDel, eventCompletions(noCompletions))},
	};

}
