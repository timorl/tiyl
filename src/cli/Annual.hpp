#ifndef TIYL_CLI_ANNUAL_HPP
#define TIYL_CLI_ANNUAL_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"projects/Annual.hpp"

namespace cli {

	using Annual = projects::Annual;
	using Annuals = projects::Annuals;

	void printAnnualNames(Annuals const & annuals);

	int annualAdd(Context & c, Arguments const & args);

	int annualDel(Context & c, Arguments const & args);

	int annualList(Context & c, Arguments const &);

	int annualShow(Context & c, Arguments const & args);

	int annual(Context & c, Arguments const & args);

	const std::map<std::string, Command> annualCommands = {
		{"list", annualList},
		{"show", annualShow},
		{"add", annualAdd},
		{"del", annualDel},
	};

}
#endif
