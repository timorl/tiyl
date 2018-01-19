#include"cli/Project.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Todo.hpp"

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
			std::cout << "No actions." << std::endl;
			return;
		}
		std::cout << "Actions:" << std::endl;
		for (Todo const & action : actions) {
			std::cout << " ";
			printAction(action);
		}
	}

	void printSubprojectNames(Subprojects const & subprojects) {
		if (subprojects.empty()) {
			std::cout << "No subprojects." << std::endl;
			return;
		}
		std::cout << "Subprojects:" << std::endl;
		for (Subproject const & subproject : subprojects) {
			std::cout << " ";
			std::cout << subproject.first << std::endl;
		}
	}

	int projectShow(Context & c, std::vector<std::string> const &) {
		Project const & project = c.getProject();
		Subprojects const & subprojects = project.getSubprojects();
		TodoList const & actions = project.getActions();
		std::cout << "Project: " << c.getCurrentName() << std::endl;
		std::cout << "Description: " << project.getDescription() << std::endl;
		std::cout << "This project is " << (project.isActionable()?"":"not") << " actionable." << std::endl;
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
