#include"cli/Project.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Mess.hpp"
#include"projects/Todo.hpp"
#include"cli/Pretty.hpp"
#include"cli/Todo.hpp"
#include"cli/Mess.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;
	using Mess = projects::Mess;
	using Todo = projects::Todo;
	using TodoList = projects::TodoList;

	void printSubprojectShort(Subproject const & subproject) {
		std::string toPrint = subproject.first;
		Project const & project = subproject.second;
		if (project.isFrozen()) {
			toPrint = cyan(toPrint);
		} else if (!project.isActionable()) {
			toPrint = red(toPrint);
		}
		std::cout << toPrint << std::endl;
	}

	void printSubprojectNames(Subprojects const & subprojects) {
		if (subprojects.empty()) {
			std::cout << lessVisible("No subprojects.") << std::endl;
			return;
		}
		std::cout << brightWhite("Subprojects:") << std::endl;
		for (Subproject const & subproject : subprojects) {
			std::cout << " ";
			printSubprojectShort(subproject);
		}
	}

	int projectShow(Context & c, std::vector<std::string> const &) {
		Project const & project = c.getProject();
		Subprojects const & subprojects = project.getSubprojects();
		Mess const & mess = project.getMess();
		TodoList const & todos = project.getTodos();
		std::cout << brightWhite("Project: ") << c.getCurrentName() << std::endl;
		std::cout << brightWhite("Description: ") << project.getDescription() << std::endl;
		if (project.isFrozen()) {
			std::cout << "This project is " << cyan("frozen") << "." << std::endl;
		} else {
			std::cout << "This project is" << (project.isActionable()?"":red(" not")) << " actionable." << std::endl;
		}
		printMess(mess);
		printTodoNames(todos);
		printSubprojectNames(subprojects);
		return 0;
	}

	int projectFreeze(Context & c, std::vector<std::string> const &) {
		c.freeze();
		return 0;
	}

	int projectThaw(Context & c, std::vector<std::string> const &) {
		c.thaw();
		return 0;
	}

	int projectDelete(Context & c, std::vector<std::string> const & args) {
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
		std::string subprojectName = names[subprojectId];
		if (!subprojects.at(subprojectName).empty()) {
			if (!confirmation("The chosen subproject is not empty.")) {
				return 3;
			}
		}
		c.delSubproject(subprojectName);
		return 0;
	}

	Subproject buildSubproject(std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string name = splitSubcommand(args, newArgs, "");
		if (name.empty()) {
			std::cout << "Name: ";
			std::getline(std::cin, name);
		}
		std::string description;
		if (!newArgs.empty()) {
			description = newArgs[0];
		} else {
			std::cout << "Description: ";
			std::getline(std::cin, description);
		}
		return Subproject(std::move(name), Project(description));
	}

	int projectCreate(Context & c, std::vector<std::string> const & args) {
		if (!c.addSubproject(buildSubproject(args))) {
			std::cout << "Subproject name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int project(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "show");
		return singleCommand(projectCommands, c, subcommand, newArgs);
	}

}
