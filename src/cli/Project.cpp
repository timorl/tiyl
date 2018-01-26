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
		Mess const & mess = project.getMess();
		TodoList const & todos = project.getTodos();
		std::cout << brightWhite("Project: ") << c.getCurrentName() << std::endl;
		std::cout << brightWhite("Description: ") << project.getDescription() << std::endl;
		std::cout << "This project is" << (project.isActionable()?"":red(" not")) << " actionable." << std::endl;
		printMess(mess);
		printTodoNames(todos);
		printSubprojectNames(subprojects);
		return 0;
	}

	int project(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "show");
		return singleCommand(projectCommands, c, subcommand, newArgs);
	}

}
