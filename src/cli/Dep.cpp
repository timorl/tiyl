#include"cli/Dep.hpp"
#include"cli/Utils.hpp"

#include<iostream>

namespace cli {

	int depAdd(Context & c, Arguments const & args) {
		Arguments a = args;
		std::string what = chooseFrom(keyVector(c.getProject().getPossibleDependents()), a, "dependent");
		std::string onWhat = chooseFrom(keyVector(c.getProject().getPossibleDependencies()), a, "dependency");
		if ( !c.addDependency(what, onWhat) ) {
			std::cout << "Incorrect dependency." << std::endl;
			return 1;
		}
		return 0;
	}

	int dep(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "add");
		return singleCommand(depCommands, c, subcommand, newArgs);
	}

	const Commands depCommands = {
		{"add", Command(depAdd, dependentCompletions(dependencyCompletions(noCompletions)))},
	};

}
