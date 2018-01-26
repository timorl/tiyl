#include"cli/Mess.hpp"

#include<iostream>

#include"projects/Mess.hpp"
#include"cli/Pretty.hpp"
#include"cli/Movement.hpp"
#include"cli/Todo.hpp"

namespace cli {

	using Mess = projects::Mess;

	int messAdd(Context & c, std::vector<std::string> const & args) {
		std::string name;
		if ( !args.empty() ) {
			name = args[0];
		} else {
			std::cout << "Name: ";
			std::getline(std::cin, name);
		}
		c.addMess(name);
		return 0;
	}

	int deleteFix(Context & c, std::vector<std::string> const &, std::string const & messItem) {
		c.delMess(messItem);
		return 0;
	}

	int downFix(Context & c, std::vector<std::string> const & args, std::string const & messItem) {
		int downRes = down(c, args);
		if (downRes != 0) {
			return downRes;
		}
		c.addMess(messItem);
		up(c, args);
		c.delMess(messItem);
		return 0;
	}

	int todoFix(Context & c, std::vector<std::string> const & args, std::string const & messItem) {
		int todoRes = todoAdd(c, args);
		if ( todoRes != 0 ) {
			return todoRes;
		}
		c.delMess(messItem);
		return 0;
	}

	const std::vector<std::function<int(Context &, std::vector<std::string> const &, std::string const &)>> fixes = {
		deleteFix,
		downFix,
		todoFix,
	};

	int messFixer(Context & c, std::vector<std::string> const & args, std::string const & messItem) {
		std::vector<std::string> newArgs;
		std::string methodChoice = splitSubcommand(args, newArgs, "");
		std::vector<std::string> options{"Delete", "Push down", "Convert to todo"};
		int optionId;
		if ( !methodChoice.empty() ) {
			optionId = decodeChoice(options, "option", methodChoice);
		} else {
			optionId = requestChoice(options, "option");
		}
		if (optionId == -1) {
			return 1;
		}
		return fixes[optionId](c, newArgs, messItem);
	}

	int messFix(Context & c, std::vector<std::string> const & args) {
		Mess const & mess = c.getProject().getMess();
		if (mess.empty()) {
			std::cout << "No mess." << std::endl;
			return 2;
		}
		std::vector<std::string> names;
		for (std::string const & m : mess) {
			names.push_back(m);
		}
	 std::vector<std::string> newArgs;
		std::string messChoice = splitSubcommand(args, newArgs, "");
		int messId;
		if ( !messChoice.empty() ) {
			messId = decodeChoice(names, "mess", messChoice);
		} else {
			messId = requestChoice(names, "mess");
		}
		if (messId == -1) {
			return 1;
		}
		std::string messItem = names.at(messId);
		return messFixer(c, newArgs, messItem);
	}

	void printMess(Mess const & mess) {
		if (mess.empty()) {
			std::cout << lessVisible("No mess.") << std::endl;
			return;
		}
		std::cout << brightWhite("Mess:") << std::endl;
		for (std::string const & m : mess) {
			std::cout << " ";
			std::cout << red(m) << std::endl;
		}
	}

	int messList(Context & c, std::vector<std::string> const &) {
		Mess const & mess = c.getProject().getMess();
		printMess(mess);
		return 0;
	}

	int mess(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(messCommands, c, subcommand, newArgs);
	}

}
