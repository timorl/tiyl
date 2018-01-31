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

	int decodeChoice(std::vector<std::string> const & from, std::string const & what, std::string answer) {
		unsigned int id;
		try {
			id = std::stoul(answer);
		} catch (...) {
			std::cout << "Pick a natural number." << std::endl;
			return -1;
		}
		if ( id >= from.size() ) {
			std::cout << "No " << what << " with id " << id << "." << std::endl;
			return -1;
		}
		return id;
	}

	int requestChoice(std::vector<std::string> const & from, std::string const & what) {
		std::cout << "Pick a " << what << ":" << std::endl;
		for (unsigned int i = 0; i < from.size(); i++) {
			std::cout << i << ". " << from.at(i) << std::endl;
		}
		int choice = -1;
		while ( choice == -1 ) {
			std::cout << "Your choice: ";
			std::string answer;
			if ( !std::getline(std::cin, answer) ) {
				std::cin.clear();
				return -1;
			}
			choice = decodeChoice(from, what, answer);
		}
		return choice;
	}

	const std::set<std::string> meansYes{"y", "Y", "yes", "Yes"};

	bool confirmation(std::string problem) {
		std::string answer;
		std::cout << problem << " Are you sure you want to continue [y/N]? ";
		std::getline(std::cin, answer);
		if ( meansYes.count(answer) ) {
			return true;
		}
		return false;
	}

}
