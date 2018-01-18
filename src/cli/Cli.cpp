#include"cli/Cli.hpp"

#include<iostream>

namespace cli {

	void unknownCommandError(std::string const & name) {
		std::cout << "Unknown command: " << name << std::endl;
	}

	bool prompt(Context &, std::string & input) {
		std::cout << "tiyl> ";
		if (std::getline(std::cin, input)) {
			return true;
		}
		return false;
	}

	int singleCommand(Context & c, std::string const & name, std::vector<std::string> const & args) {
		if (commands.count(name) == 0) {
			unknownCommandError(name);
			return -1;
		}
		return commands.at(name)(c, args);
	}

	void commandLine(Context & c) {
		std::string input;
		while (prompt(c, input)) {
			if (input.length() == 0) {
				continue;
			}
			std::istringstream inputStream(input);
			std::string name;
			inputStream >> name;
			if (name.length() == 0) {
				continue;
			}
			std::vector<std::string> args;
			std::copy(std::istream_iterator<std::string>(inputStream), std::istream_iterator<std::string>(), std::back_inserter(args));
			c.setLastResult(singleCommand(c, name, args));
		}
		std::cout << "Bye!" << std::endl;
	}

}
