#include"cli/Commands.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Mess.hpp"
#include"projects/Todo.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;
	using TodoList = projects::TodoList;
	using Mess = projects::Mess;

	int status(Context & c, std::vector<std::string> const &) {
		Mess const & mess = c.getMess();
		Project const & project = c.getProject();
		int messSize = mess.size();
		Subprojects all;
		project.accumulateFromSubprojects(all, projects::accumulateAll);
		int allSize = all.size();
		TodoList actions;
		project.accumulateFromSubprojects(actions, projects::accumulateActions);
		int actionsSize = actions.size();
		Subprojects nonactionable;
		project.accumulateFromSubprojects(nonactionable, projects::accumulateNonactionable);
		int nonactionableSize = nonactionable.size();
		std::cout << "You have a mess of size: " << messSize << std::endl;
		std::cout << "You have " << allSize << " projects." << std::endl;
		std::cout << "Among those " << nonactionableSize << " are nonactionable." << std::endl;
		std::cout << "You can take " << actionsSize << " actions." << std::endl;
		return 0;
	}

	int down(Context & c, std::vector<std::string> const & args) {
		Project const & project = c.getProject();
		Subprojects const & subprojects = project.getSubprojects();
		std::vector<std::string> names;
		for (Subproject const & subproject : subprojects) {
			names.push_back(subproject.first);
		}
		std::string subprojectName;
		if ( !args.empty() ) {
			subprojectName = names[std::stoi(args[0])];
		} else {
			subprojectName = requestChoice(names, "subproject");
		}
		if ( c.moveToChild(subprojectName) ) {
			std::cout << "Moving to " << subprojectName << "." << std::endl;
			return 0;
		}
		return 1;
	}

	int up(Context & c, std::vector<std::string> const &) {
		c.moveUp();
		return 0;
	}

	int top(Context & c, std::vector<std::string> const &) {
		c.moveTop();
		return 0;
	}

}