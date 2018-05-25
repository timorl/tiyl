#include"cli/Annual.hpp"

#include<iostream>

#include"cli/Pretty.hpp"
#include"cli/Utils.hpp"

namespace cli {

	using AnnualDetails = projects::AnnualDetails;

	void printAnnual(Annual const & a) {
		std::cout << "Name: " << a.first << std::endl;
		AnnualDetails const & details = a.second;
		std::cout << "Closest occurence: " << util::dateToString(details.getWhen()) << std::endl;
		std::set<std::string> const & dependencies = details.getDependencies();
		if (!dependencies.empty()) {
			std::cout << "Depends on: " << std::endl;
			for (std::string const & dep : dependencies) {
				std::cout << " " << dep << std::endl;
			}
		}
	}

	void printAnnualShort(Annual const & a) {
		std::string name = a.first;
		AnnualDetails const & annual = a.second;
		int daysLeft = annual.daysLeft();
		std::string dateToPrint = util::dateToString(annual.getWhen());
		if (daysLeft < 3) {
			dateToPrint = red(dateToPrint);
		}
		if (!a.second.getDependencies().empty()) {
			name = red(name);
		}
		std::cout << name << "(" << dateToPrint << ")" << std::endl;
	}

	void printAnnualNames(Annuals const & annuals) {
		if (annuals.empty()) {
			std::cout << lessVisible("No annuals.") << std::endl;
			return;
		}
		std::cout << brightWhite("Annuals:") << std::endl;
		for (Annual const & a : annuals) {
			std::cout << " ";
			printAnnualShort(a);
		}
	}

	Annual buildAnnual(Arguments const & args) {
		Arguments a = args;
		std::string name = requestString("Name", a);
		Date when = requestAnnual("Date (mm-dd)", a);
		return Annual(std::move(name), AnnualDetails(when));
	}

	int annualAdd(Context & c, Arguments const & args) {
		if ( !c.addAnnual( buildAnnual(args) ) ) {
			std::cout << "Annual name conflict." << std::endl;
			return 1;
		}
		return 0;
	}

	int annualDel(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Annuals const & annuals = c.getProject().getAnnuals();
		if (annuals.empty()) {
			std::cout << "No annuals." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(annuals), a, "annual");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		c.delAnnual(name);
		c.moveUp(path);
		return 0;
	}

	int annualList(Context & c, Arguments const &) {
		Annuals const & annuals = c.getProject().getAnnuals();
		printAnnualNames(annuals);
		return 0;
	}

	int annualShow(Context & c, Arguments const & args) {
		ProjectPath path;
		Arguments a = args;
		if (!moveDownWithArgs(c, a, path)) {
			return 3;
		}
		Annuals const & annuals = c.getProject().getAnnuals();
		if (annuals.empty()) {
			std::cout << "No annuals." << std::endl;
			c.moveUp(path);
			return 2;
		}
		std::string name = chooseFrom(keyVector(annuals), a, "annual");
		if (name.empty()) {
			c.moveUp(path);
			return 1;
		}
		printAnnual(Annual(name, annuals.at(name)));
		c.moveUp(path);
		return 0;
	}

	int annual(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(annualCommands, c, subcommand, newArgs);
	}

	const Commands annualCommands = {
		{"list", Command(annualList, noCompletions)},
		{"show", Command(annualShow, annualCompletions(noCompletions))},
		{"add", Command(annualAdd, noCompletions)},
		{"del", Command(annualDel, annualCompletions(noCompletions))},
	};

}
