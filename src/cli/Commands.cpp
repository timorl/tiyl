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
		Project const & project = c.getProject();
		Mess mess = project.getMess();
		project.accumulateFromSubprojects(mess, projects::accumulateMess);
		int messSize = mess.size();
		Subprojects all;
		project.accumulateFromSubprojects(all, projects::accumulateAll);
		int allSize = all.size();
		TodoList actions;
		project.accumulateFromSubprojects(actions, projects::accumulateTodos);
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

}
