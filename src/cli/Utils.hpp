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

	std::string requestString(std::string const & name, Arguments & args);

	int requestInt(std::string const & name, Arguments & args, int def);

	template<typename T>
	std::string chooseFrom(std::map<std::string, T> const & pool, Arguments & args, std::string const & what) {
		std::vector<std::string> names;
		for (std::pair<std::string, T> const & a : pool) {
			names.push_back(a.first);
		}
		Arguments newArgs;
		std::string ans = splitSubcommand(args, newArgs, "");
		args = newArgs;
		int id;
		if ( !ans.empty() ) {
			id = decodeChoice(names, what, ans);
		} else {
			id = requestChoice(names, what);
		}
		if (id == -1) {
			return "";
		}
		return names.at(id);
	}

	std::string chooseFromMess(Mess const & pool, Arguments & args, std::string const & what);

}
#endif
