#include"cli/Action.hpp"

#include<iostream>

#include"cli/Pretty.hpp"

namespace cli {

	using ActionDetails = projects::ActionDetails;

	void printAction(Action const & a) {
		std::cout << "Name: " << a.first << std::endl;
		ActionDetails const & details = a.second;
		if (details.getDuration() != 0) {
			std::cout << "Expected duration: " << details.getDuration() << " minutes." << std::endl;
		}
		std::set<std::string> const & dependencies = details.getDependencies();
		if (!dependencies.empty()) {
			std::cout << "Depends on: " << std::endl;
			for (std::string const & dep : dependencies) {
				std::cout << " " << dep << std::endl;
			}
		}
	}

	void printActionShort(Action const & a) {
		std::string toPrint = a.first;
		if (!a.second.getDependencies().empty()) {
			toPrint = lessVisible(toPrint);
		}
		std::cout << toPrint;
		if (a.second.getDuration() != 0) {
			std::cout << " (" << a.second.getDuration() << "m)";
		}
		std::cout << std::endl;
	}

	void printActionNames(Actions const & actions) {
		if (actions.empty()) {
			std::cout << lessVisible("No actions.") << std::endl;
			return;
		}
		std::cout << brightWhite("Actions:") << std::endl;
		for (Action const & a : actions) {
			std::cout << " ";
			printActionShort(a);
		}
	}

	int actionDone(Context & c, Arguments const & args) {
		Actions const & actions = c.getProject().getActions();
		if (actions.empty()) {
			std::cout << "No actions." << std::endl;
			return 2;
		}
		Arguments a = args;
		std::string name = chooseFrom(actions, a, "action");
		if (name.empty()) {
			return 1;
		}
		c.delAction(name);
		return 0;
	}

	Action buildAction(Arguments const & args) {
		Arguments a = args;
		std::string name = requestString("Name", a);
		int duration = requestInt("Duration (in minutes)", a, 0);
		return Action(std::move(name), ActionDetails(duration));
	}

	int actionAdd(Context & c, Arguments const & args) {
		if ( !c.addAction( buildAction(args) ) ) {
			std::cout << "Action name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int actionList(Context & c, Arguments const &) {
		Actions const & actions = c.getProject().getActions();
		printActionNames(actions);
		return 0;
	}

	int actionShow(Context & c, Arguments const & args) {
		Actions const & actions = c.getProject().getActions();
		if (actions.empty()) {
			std::cout << "No actions." << std::endl;
			return 2;
		}
		Arguments a = args;
		std::string name = chooseFrom(actions, a, "action");
		printAction(Action(name, actions.at(name)));
		return 0;
	}

	int action(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(actionCommands, c, subcommand, newArgs);
	}

}
