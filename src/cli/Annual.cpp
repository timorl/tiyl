#include"cli/Annual.hpp"

#include<iostream>

#include"cli/Pretty.hpp"

namespace cli {

	using AnnualDetails = projects::AnnualDetails;

	void printAnnual(Annual const & a) {
		std::cout << "Name: " << a.first << std::endl;
		AnnualDetails const & details = a.second;
		std::cout << "Closest occurence: " << util::dateToString(details.getWhen()) << std::endl;
	}

	void printAnnualShort(Annual const & a) {
		std::string name = a.first;
		AnnualDetails const & annual = a.second;
		int daysLeft = annual.daysLeft();
		std::string dateToPrint = util::dateToString(annual.getWhen());
		if (daysLeft < 21) {
			dateToPrint = red(dateToPrint);
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
		Annuals const & annuals = c.getProject().getAnnuals();
		if (annuals.empty()) {
			std::cout << "No annuals." << std::endl;
			return 2;
		}
		Arguments a = args;
		std::string name = chooseFrom(annuals, a, "annual");
		if (name.empty()) {
			return 1;
		}
		c.delAnnual(name);
		return 0;
	}

	int annualList(Context & c, Arguments const &) {
		Annuals const & annuals = c.getProject().getAnnuals();
		printAnnualNames(annuals);
		return 0;
	}

	int annualShow(Context & c, Arguments const & args) {
		Annuals const & annuals = c.getProject().getAnnuals();
		if (annuals.empty()) {
			std::cout << "No annuals." << std::endl;
			return 2;
		}
		Arguments a = args;
		std::string name = chooseFrom(annuals, a, "annual");
		if (name.empty()) {
			return 1;
		}
		printAnnual(Annual(name, annuals.at(name)));
		return 0;
	}

	int annual(Context & c, Arguments const & args) {
		Arguments newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(annualCommands, c, subcommand, newArgs);
	}

}