#ifndef TIYL_CLI_CLI_HPP
#define TIYL_CLI_CLI_HPP
#include<string>
#include<vector>

#include"cli/Context.hpp"
#include"cli/Commands.hpp"

namespace cli {

	int singleCommand(Context & c, std::string const & name, std::vector<std::string> const & args);

	void commandLine(Context & c);

}
#endif
