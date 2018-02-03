#include"cli/Commands.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Mess.hpp"
#include"projects/Action.hpp"
#include"cli/All.hpp"
#include"cli/Pretty.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;
	using Actions = projects::Actions;
	using Habits = projects::Habits;
	using Mess = projects::Mess;

	int statusShort(Context & c, Arguments const &) {
		Project const & project = c.getProject();
		Mess mess = project.getMess();
		project.accumulateFromSubprojects(mess, projects::accumulateMess);
		int messSize = mess.size();
		Actions actions;
		project.accumulateFromSubprojects(actions, projects::accumulateActions);
		int actionsSize = actions.size();
		Subprojects nonactionable;
		project.accumulateFromSubprojects(nonactionable, projects::accumulateNonactionable);
		int nonactionableSize = nonactionable.size();
		Habits dueHabits;
		project.accumulateFromSubprojects(dueHabits, accumulateDueHabits);
		int dueHabitsSize = dueHabits.size();
		Habits pastHabits;
		project.accumulateFromSubprojects(pastHabits, accumulatePastHabits);
		int pastHabitsSize = pastHabits.size();
		if (messSize > 0) {
			std::cout << "M:" << red(std::to_string(messSize)) << " ";
		}
		if (nonactionableSize > 0) {
			std::cout << "NP:" << red(std::to_string(nonactionableSize)) << " ";
		}
		std::cout << "A:" << actionsSize << " ";
		std::cout << "H:" << dueHabitsSize;
		if (pastHabitsSize > 0) {
			std::cout << "(" << red(std::to_string(dueHabitsSize)) << ")";
		}
		std::cout << std::endl;
		return 0;
	}

	int statusLong(Context & c, Arguments const &) {
		Project const & project = c.getProject();
		Mess mess = project.getMess();
		project.accumulateFromSubprojects(mess, projects::accumulateMess);
		int messSize = mess.size();
		Subprojects all;
		project.accumulateFromSubprojects(all, projects::accumulateAll);
		int allSize = all.size();
		Actions actions;
		project.accumulateFromSubprojects(actions, projects::accumulateActions);
		int actionsSize = actions.size();
		Subprojects nonactionable;
		project.accumulateFromSubprojects(nonactionable, projects::accumulateNonactionable);
		int nonactionableSize = nonactionable.size();
		Habits dueHabits;
		project.accumulateFromSubprojects(dueHabits, accumulateDueHabits);
		int dueHabitsSize = dueHabits.size();
		Habits pastHabits;
		project.accumulateFromSubprojects(pastHabits, accumulatePastHabits);
		int pastHabitsSize = pastHabits.size();
		std::cout << "You have a mess of size: " << messSize << std::endl;
		std::cout << "You have " << allSize << " projects." << std::endl;
		std::cout << "Among those " << nonactionableSize << " are nonactionable." << std::endl;
		std::cout << "You can take " << actionsSize << " actions." << std::endl;
		std::cout << "You have " << dueHabitsSize << " due habits." << std::endl;
		std::cout << "Among those " << pastHabitsSize << " are past due." << std::endl;
		return 0;
	}

	int status(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "short");
		return singleCommand(statusCommands, c, subcommand, newArgs);
	}

}
