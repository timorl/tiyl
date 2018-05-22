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

	int decodeNumber(std::string answer) {
	 int result = -1;
		try {
			result = std::stoul(answer);
		} catch (...) {
			std::cout << "Pick a natural number." << std::endl;
		}
		return result;
	}

	Date decodeDate(std::string answer) {
		return util::stringToDate(answer);
	}

	Date decodeAnnual(std::string answer) {
		return util::stringToAnnual(answer);
	}

	std::string decodeChoice(std::vector<std::string> const & from, std::string const & what, std::string answer) {
		if (std::find(from.begin(), from.end(), answer) != from.end()) {
			return answer;
		}
		int pid;
		pid = decodeNumber(answer);
		if (pid < 0) {
			return "";
		}
		unsigned int id = pid;
		if (id >= from.size()) {
			std::cout << "No " << what << " with id " << id << "." << std::endl;
			return "";
		}
		return from.at(id);
	}

	std::string requestChoice(std::vector<std::string> const & from, std::string const & what) {
		std::cout << "Pick a " << what << ":" << std::endl;
		for (unsigned int i = 0; i < from.size(); i++) {
			std::cout << i << ". " << from.at(i) << std::endl;
		}
		std::string choice("");
		while (choice.empty()) {
			std::cout << "Your choice: ";
			std::string answer;
			if ( !std::getline(std::cin, answer) ) {
				std::cin.clear();
				return "";
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

	std::string requestString(std::string const & name, Arguments & args) {
		Arguments newArgs;
		std::string result = splitSubcommand(args, newArgs, "");
		args = newArgs;
		if ( result.empty() ) {
			std::cout << name << ": ";
			std::getline(std::cin, result);
		}
		return result;
	}

	int requestInt(std::string const & name, Arguments & args, int def) {
		Arguments newArgs;
		int result = -1;
		std::string ans = splitSubcommand(args, newArgs, "");
		args = newArgs;
		if ( !ans.empty() ) {
			result = decodeNumber(ans);
		}
		if ( result == -1 ) {
			args = Arguments();
			std::cout << name << " [" << def << "]: ";
			std::getline(std::cin, ans);
			result = decodeNumber(ans);
		}
		if (result == -1) {
			result = def;
		}
		return result;
	}

	Date requestDate(std::string const & name, Arguments & args) {
		Arguments newArgs;
		Date result = util::maxDate();
		std::string ans = splitSubcommand(args, newArgs, "");
		args = newArgs;
		if ( !ans.empty() ) {
			result = decodeDate(ans);
		}
		if ( result == util::maxDate() ) {
			args = Arguments();
			std::cout << name << ": ";
			std::getline(std::cin, ans);
			result = decodeDate(ans);
		}
		return result;
	}

	Date requestAnnual(std::string const & name, Arguments & args) {
		Arguments newArgs;
		Date result = util::maxDate();
		std::string ans = splitSubcommand(args, newArgs, "");
		args = newArgs;
		if ( !ans.empty() ) {
			result = decodeAnnual(ans);
		}
		if ( result == util::maxDate() ) {
			args = Arguments();
			std::cout << name << ": ";
			std::getline(std::cin, ans);
			result = decodeAnnual(ans);
		}
		return result;
	}

	std::vector<std::string> keyVector(std::set<std::string> const & pool) {
		std::vector<std::string> result;
		for (std::string const & a : pool) {
			result.push_back(a);
		}
		return result;
	}

	std::string chooseFrom(std::vector<std::string> const & names, Arguments & args, std::string const & what) {
		Arguments newArgs;
		std::string ans = splitSubcommand(args, newArgs, "");
		args = newArgs;
		std::string result("");
		if ( !ans.empty() ) {
			result = decodeChoice(names, what, ans);
		} else {
			result = requestChoice(names, what);
		}
		return result;
	}

}
