#include"cli/Commands.hpp"

#include<iostream>

#include"projects/Project.hpp"

namespace cli {

	using Subprojects = projects::Subprojects;

	int down(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!a.empty() && !a[0].empty() && a[0].back() != '/') {
			a[0] += '/';
		}
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		if (!path.empty()) {
			return 0;
		}
		Subprojects const & subprojects = c.getProject().getSubprojects();
		if (subprojects.empty()) {
			std::cout << "No subprojects." << std::endl;
			return 2;
		}
		std::string name = chooseFrom(keyVector(subprojects), a, "subproject");
		if ( c.moveToChild(name) ) {
			return 0;
		}
		return 1;
	}

	int up(Context & c, Arguments const &) {
		c.moveUp();
		return 0;
	}

	int top(Context & c, Arguments const &) {
		c.moveTop();
		return 0;
	}

}
