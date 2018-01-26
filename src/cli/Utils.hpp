#ifndef TIYL_CLI_UTILS_HPP
#define TIYL_CLI_UTILS_HPP
#include<string>
#include<vector>
#include<map>

#include"cli/Context.hpp"

namespace cli {

	using Command = std::function<int(Context &, std::vector<std::string> const &)>;
 using Commands = std::map<std::string, Command>;
	using Arguments = std::vector<std::string>;

	int singleCommand(Commands const & commands, Context & c, std::string const & name, Arguments const & args);

	std::string splitSubcommand(Arguments const & oldArgs, Arguments & newArgs, std::string const & defaultCommand);

	int decodeChoice(std::vector<std::string> const & from, std::string const & what, std::string answer);

	int requestChoice(std::vector<std::string> const & from, std::string const & what);

}
#endif
