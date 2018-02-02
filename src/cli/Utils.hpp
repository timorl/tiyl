#ifndef TIYL_CLI_UTILS_HPP
#define TIYL_CLI_UTILS_HPP
#include<string>
#include<vector>
#include<map>

#include"cli/Context.hpp"

namespace cli {

	using Arguments = std::vector<std::string>;
	using Command = std::function<int(Context &, Arguments const &)>;
 using Commands = std::map<std::string, Command>;

	int singleCommand(Commands const & commands, Context & c, std::string const & name, Arguments const & args);

	std::string splitSubcommand(Arguments const & oldArgs, Arguments & newArgs, std::string const & defaultCommand);

	int decodeNumber(std::string answer);

	int decodeChoice(std::vector<std::string> const & from, std::string const & what, std::string answer);

	int requestChoice(std::vector<std::string> const & from, std::string const & what);

	bool confirmation(std::string problem);

}
#endif
