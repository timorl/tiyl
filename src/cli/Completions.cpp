#include"cli/Utils.hpp"

#include<string>
#include<vector>
#include<algorithm>

namespace cli {

	Completions noCompletions(Context const &, Arguments const &) {
		return Completions();
	}

	CompletionFunction subcommandCompletions(Commands const & subcommands) {
		return [&subcommands](Context const & c, Arguments const & args) -> Completions {
			std::vector<std::string> subcommandNames;
			for (auto const & cmd : subcommands) {
				subcommandNames.push_back(cmd.first + " ");
			}
			Arguments newArgs;
			std::string maybeName = splitSubcommand(args, newArgs, "");
			if (maybeName.length() == 0) {
				return subcommandNames;
			}
			Completions result;
			if (subcommands.count(maybeName)) {
				result = subcommands.at(maybeName).completions(c, newArgs);
				for (std::string & cmpl : result) {
					cmpl = maybeName + " " + cmpl;
				}
				return result;
			}
			for (std::string const & cmdName : subcommandNames) {
				if (std::equal(maybeName.begin(), maybeName.end(), cmdName.begin())) {
					result.push_back(cmdName);
				}
			}
			return result;
		};
	}

}
