#include"cli/Commands.hpp"

#include<iostream>

#include"projects/Project.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;

	int down(Context & c, std::vector<std::string> const & args) {
		Project const & project = c.getProject();
		Subprojects const & subprojects = project.getSubprojects();
		if (subprojects.empty()) {
			std::cout << "No subprojects." << std::endl;
			return 2;
		}
		std::vector<std::string> names;
		for (Subproject const & subproject : subprojects) {
			names.push_back(subproject.first);
		}
		int subprojectId;
		if ( !args.empty() ) {
			subprojectId = decodeChoice(names, "subproject", args[0]);
		} else {
			subprojectId = requestChoice(names, "subproject");
		}
		if ( subprojectId == -1 ) {
			return 1;
		}
		if ( c.moveToChild(names.at(subprojectId)) ) {
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
