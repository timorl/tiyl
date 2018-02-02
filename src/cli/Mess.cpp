#include"cli/Mess.hpp"

#include<iostream>

#include"projects/Mess.hpp"
#include"cli/Pretty.hpp"
#include"cli/Movement.hpp"
#include"cli/Action.hpp"
#include"cli/Project.hpp"

namespace cli {

	using Mess = projects::Mess;

	int messAdd(Context & c, Arguments const & args) {
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

	int deleteFix(Context & c, Arguments const &, std::string const & messItem) {
		c.delMess(messItem);
		return 0;
	}

	int downFix(Context & c, Arguments const & args, std::string const & messItem) {
		int downRes = down(c, args);
		if (downRes != 0) {
			return downRes;
		}
		c.addMess(messItem);
		up(c, args);
		c.delMess(messItem);
		return 0;
	}

	int actionFix(Context & c, Arguments const & args, std::string const & messItem) {
		int actionRes = actionAdd(c, args);
		if ( actionRes != 0 ) {
			return actionRes;
		}
		c.delMess(messItem);
		return 0;
	}

	int subprojectFix(Context & c, Arguments const & args, std::string const & messItem) {
		int subprojectRes = projectCreate(c, args);
		if ( subprojectRes != 0 ) {
			return subprojectRes;
		}
		c.delMess(messItem);
		return 0;
	}

	const std::vector<std::function<int(Context &, Arguments const &, std::string const &)>> fixes = {
		deleteFix,
		downFix,
		actionFix,
		subprojectFix,
	};

	int messFixer(Context & c, Arguments const & args, std::string const & messItem) {
		Arguments newArgs;
		std::string methodChoice = splitSubcommand(args, newArgs, "");
		std::vector<std::string> options{"Delete", "Push down", "Convert to action", "Convert to subproject"};
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

	int messFix(Context & c, Arguments const & args) {
		Mess const & mess = c.getProject().getMess();
		if (mess.empty()) {
			std::cout << "No mess." << std::endl;
			return 2;
		}
		std::vector<std::string> names;
		for (std::string const & m : mess) {
			names.push_back(m);
		}
	 Arguments newArgs;
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

	int messList(Context & c, Arguments const &) {
		Mess const & mess = c.getProject().getMess();
		printMess(mess);
		return 0;
	}

	int mess(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(messCommands, c, subcommand, newArgs);
	}

}
