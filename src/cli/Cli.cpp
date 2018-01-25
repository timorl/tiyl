#include"cli/Cli.hpp"

#include<iostream>

namespace cli {

	bool prompt(Context & c, std::string & input) {
		std::cout << c.getCurrentName() << "> ";
		if (std::getline(std::cin, input)) {
			return true;
		}
		return false;
	}

	void commandLine(Context & c, std::function<void(Context &)> save) {
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
			save(c);
		}
		std::cout << "Bye!" << std::endl;
	}

}
