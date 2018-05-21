#include"cli/Project.hpp"

#include<iostream>

#include"projects/Project.hpp"
#include"projects/Mess.hpp"
#include"projects/Habit.hpp"
#include"projects/Action.hpp"
#include"cli/Pretty.hpp"
#include"cli/Utils.hpp"
#include"cli/Action.hpp"
#include"cli/Habit.hpp"
#include"cli/Event.hpp"
#include"cli/Annual.hpp"
#include"cli/Mess.hpp"

namespace cli {

	using Project = projects::Project;
	using Subprojects = projects::Subprojects;
	using Subproject = projects::Subproject;
	using Mess = projects::Mess;
	using Action = projects::Action;
	using Actions = projects::Actions;
	using Habits = projects::Habits;
	using Events = projects::Events;
	using Annuals = projects::Annuals;

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

	int projectShow(Context & c, Arguments const &) {
		Project const & project = c.getProject();
		Subprojects const & subprojects = project.getSubprojects();
		Mess const & mess = project.getMess();
		Actions const & actions = project.getActions();
		Habits const & habits = project.getHabits();
		Events const & events = project.getEvents();
		Annuals const & annuals = project.getAnnuals();
		std::cout << brightWhite("Project: ") << c.getCurrentName() << std::endl;
		std::cout << brightWhite("Description: ") << project.getDescription() << std::endl;
		if (project.isFrozen()) {
			std::cout << "This project is " << cyan("frozen") << "." << std::endl;
		} else {
			std::cout << "This project is" << (project.isActionable()?"":red(" not")) << " actionable." << std::endl;
		}
		printMess(mess);
		printActionNames(actions);
		printHabitNames(habits);
		printEventNames(events);
		printAnnualNames(annuals);
		printSubprojectNames(subprojects);
		return 0;
	}

	int projectFreeze(Context & c, Arguments const &) {
		c.freeze();
		return 0;
	}

	int projectThaw(Context & c, Arguments const &) {
		c.thaw();
		return 0;
	}

	int projectDelete(Context & c, Arguments const & args) {
		Subprojects const & subprojects = c.getProject().getSubprojects();
		if (subprojects.empty()) {
			std::cout << "No subprojects." << std::endl;
			return 2;
		}
		Arguments a = args;
		std::string name = chooseFrom(subprojects, a, "subproject");
		if (name.empty()) {
			return 1;
		}
		if (!subprojects.at(name).empty()) {
			if (!confirmation("The chosen subproject is not empty.")) {
				return 3;
			}
		}
		c.delSubproject(name);
		return 0;
	}

	Subproject buildSubproject(Arguments const & args) {
		Arguments a = args;
		std::string name = requestString("Name", a);
		std::string description = requestString("Description", a);
		return Subproject(std::move(name), Project(description));
	}

	int projectCreate(Context & c, Arguments const & args) {
		if (!c.addSubproject(buildSubproject(args))) {
			std::cout << "Subproject name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int project(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "show");
		return singleCommand(projectCommands, c, subcommand, newArgs);
	}

}
