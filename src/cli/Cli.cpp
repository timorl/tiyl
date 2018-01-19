#include"cli/Cli.hpp"

#include<iostream>

namespace cli {

	bool prompt(Context &, std::string & input) {
		std::cout << "tiyl> ";
		if (std::getline(std::cin, input)) {
			return true;
		}
		return false;
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
			c.setLastResult(singleCommand(commands, c, name, args));
		}
		std::cout << "Bye!" << std::endl;
	}

}
