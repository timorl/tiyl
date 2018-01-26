#ifndef TIYL_CLI_MESS_HPP
#define TIYL_CLI_MESS_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"

namespace cli {

	void printMess(Mess const & mess);

	int messAdd(Context & c, std::vector<std::string> const & args);

	int messFix(Context & c, std::vector<std::string> const & args);

	int messList(Context & c, std::vector<std::string> const &);

	int mess(Context & c, std::vector<std::string> const & args);

	const std::map<std::string, Command> messCommands = {
		{"list", messList},
		{"fix", messFix},
		{"add", messAdd},
	};

}
#endif
