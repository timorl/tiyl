#include"cli/Project.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Todo.hpp"
#include"cli/Pretty.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;
	using Todo = projects::Todo;
	using TodoList = projects::TodoList;

	void printAction(Todo const & action) {
		std::cout << action << std::endl;
	}

	void printActions(TodoList const & actions) {
		if (actions.empty()) {
			std::cout << lessVisible("No actions.") << std::endl;
			return;
		}
		std::cout << brightWhite("Actions:") << std::endl;
		for (Todo const & action : actions) {
			std::cout << " ";
			printAction(action);
		}
	}

	void printSubprojectShort(Subproject const & subproject) {
		std::string toPrint = subproject.first;
		Project const & project = subproject.second;
		if (!project.isActionable()) {
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
		TodoList const & actions = project.getActions();
		std::cout << brightWhite("Project: ") << c.getCurrentName() << std::endl;
		std::cout << brightWhite("Description: ") << project.getDescription() << std::endl;
		std::cout << "This project is " << (project.isActionable()?"":red("not")) << " actionable." << std::endl;
		printActions(actions);
		printSubprojectNames(subprojects);
		return 0;
	}

	int project(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "show");
		return singleCommand(projectCommands, c, subcommand, newArgs);
	}

}
