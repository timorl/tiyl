#ifndef TIYL_CLI_UTILS_HPP
#define TIYL_CLI_UTILS_HPP
#include<string>
#include<vector>
#include<map>

#include"cli/Context.hpp"
#include"cli/Command.hpp"
#include"util/Dates.hpp"

namespace cli {

 using Date = util::Date;

	int singleCommand(Commands const & commands, Context & c, std::string const & name, Arguments const & args);

	std::string splitSubcommand(Arguments const & oldArgs, Arguments & newArgs, std::string const & defaultCommand);

	int decodeNumber(std::string answer);

	Date decodeDate(std::string answer);

	Date decodeAnnual(std::string answer);

	std::string decodeChoice(std::vector<std::string> const & from, std::string const & what, std::string answer);

	std::string requestChoice(std::vector<std::string> const & from, std::string const & what);

	bool confirmation(std::string problem);

	std::string requestString(std::string const & name, Arguments & args);

	int requestInt(std::string const & name, Arguments & args, int def);

	Date requestDate(std::string const & name, Arguments & args);

	Date requestAnnual(std::string const & name, Arguments & args);

	template<typename T>
	std::vector<std::string> keyVector(std::map<std::string, T> const & pool) {
		std::vector<std::string> result;
		for (std::pair<std::string, T> const & a : pool) {
			result.push_back(a.first);
		}
		return result;
	}

	std::vector<std::string> keyVector(std::set<std::string> const & pool);

	std::string chooseFrom(std::vector<std::string> const & names, Arguments & args, std::string const & what);

}
#endif
