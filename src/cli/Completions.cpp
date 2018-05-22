#include"cli/Utils.hpp"

#include<string>
#include<vector>
#include<algorithm>
#include<functional>

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

	const std::string quotationMark("\"");

	std::vector<std::string> quoteAndAddSpace(std::vector<std::string> const & v) {
		std::vector<std::string> result;
		for (std::string const & s : v) {
			result.push_back(quotationMark + s + quotationMark + " ");
		}
		return result;
	}

	Completions nameCompletionsRaw(std::vector<std::string> const & names, CompletionFunction const & further, Context const & c, Arguments const & args) {
		std::vector<std::string> suggestedNames = quoteAndAddSpace(names);
		Arguments newArgs;
		std::string maybeName = splitSubcommand(args, newArgs, "");
		if (maybeName.length() == 0) {
			return suggestedNames;
		}
		maybeName = quotationMark + maybeName;
		Completions result;
		if (std::find(suggestedNames.begin(), suggestedNames.end(), maybeName + quotationMark + " ") != suggestedNames.end()) {
			result = further(c, newArgs);
			for (std::string & cmpl : result) {
				cmpl = maybeName + quotationMark + " " + cmpl;
			}
			return result;
		}
		for (std::string const & name : suggestedNames) {
			if (std::equal(maybeName.begin(), maybeName.end(), name.begin())) {
				result.push_back(name);
			}
		}
		return result;
	}

	CompletionFunction nameCompletions(std::vector<std::string> const & names, CompletionFunction const & further) {
		return std::bind(nameCompletionsRaw, names, further, std::placeholders::_1, std::placeholders::_2);
	}

	CompletionFunction actionCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getActions()), further, c, args);
		};
	}

	CompletionFunction annualCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getAnnuals()), further, c, args);
		};
	}

	CompletionFunction projectCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getSubprojects()), further, c, args);
		};
	}

	CompletionFunction dependentCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getPossibleDependents()), further, c, args);
		};
	}

	CompletionFunction dependencyCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getPossibleDependencies()), further, c, args);
		};
	}

	CompletionFunction eventCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getEvents()), further, c, args);
		};
	}

	CompletionFunction habitCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getHabits()), further, c, args);
		};
	}

	CompletionFunction messCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			return nameCompletionsRaw(keyVector(c.getProject().getMess()), further, c, args);
		};
	}

}
