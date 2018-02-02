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
	}

	void printActionShort(Action const & a) {
		std::cout << a.first;
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
		std::vector<std::string> names;
		for (Action const & a : actions) {
			names.push_back(a.first);
		}
		int actionId;
		if ( !args.empty() ) {
			actionId = decodeChoice(names, "action", args[0]);
		} else {
			actionId = requestChoice(names, "action");
		}
		if (actionId == -1) {
			return 1;
		}
		c.delAction(names.at(actionId));
		return 0;
	}

	Action buildAction(Arguments const & args) {
		Arguments newArgs;
		std::string name = splitSubcommand(args, newArgs, "");
		if ( name.empty() ) {
			std::cout << "Name: ";
			std::getline(std::cin, name);
		}
		int duration = -1;
		if ( !newArgs.empty() ) {
			duration = decodeNumber(newArgs[0]);
		}
		if ( duration == -1 ) {
			std::cout << "Duration (in minutes) [0]: ";
			std::string ans;
			std::getline(std::cin, ans);
			duration = decodeNumber(ans);
		}
		if (duration == -1) {
			duration = 0;
		}
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
		std::vector<std::string> names;
		for (Action const & a : actions) {
			names.push_back(a.first);
		}
		int actionId;
		if ( !args.empty() ) {
			actionId = decodeChoice(names, "action", args[0]);
		} else {
			actionId = requestChoice(names, "action");
		}
		if (actionId == -1) {
			return 1;
		}
		std::string actionName = names.at(actionId);
		printAction(Action(actionName, actions.at(actionName)));
		return 0;
	}

	int action(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(actionCommands, c, subcommand, newArgs);
	}

}
