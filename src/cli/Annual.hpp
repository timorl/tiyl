#ifndef TIYL_CLI_ANNUAL_HPP
#define TIYL_CLI_ANNUAL_HPP

#include"cli/Command.hpp"
#include"cli/Completions.hpp"
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

	extern const Commands annualCommands;

}
#endif
