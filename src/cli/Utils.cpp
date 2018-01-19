#include"cli/Utils.hpp"

#include<iostream>

namespace cli {

	void unknownCommandError(std::string const & name) {
		std::cout << "Unknown command: " << name << std::endl;
	}

	int singleCommand(Commands const & commands, Context & c, std::string const & name, Arguments const & args) {
		if ( commands.count(name) == 0 ) {
			unknownCommandError(name);
			return -1;
		}
		return commands.at(name)(c, args);
	}

	std::string splitSubcommand(Arguments const & oldArgs, Arguments & newArgs, std::string const & defaultCommand) {
		std::string result;
		if ( oldArgs.empty() ) {
			result = defaultCommand;
		} else {
			result = oldArgs[0];
			newArgs.insert(newArgs.end(), std::next(oldArgs.begin()), oldArgs.end());
		}
		return result;
	}

	std::string requestChoice(std::vector<std::string> const & from, std::string const & what) {
		std::cout << "Pick a " << what << ":" << std::endl;
		for (unsigned int i = 0; i < from.size(); i++) {
			std::cout << i << ". " << from.at(i) << std::endl;
		}
		unsigned int choice = from.size();
		while ( choice >= from.size() ) {
			std::cout << "Your choice: ";
			std::string answer;
			std::getline(std::cin, answer);
			choice = std::stoul(answer);
		}
		return from.at(choice);
	}

}
