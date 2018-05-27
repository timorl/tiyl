#include"cli/Utils.hpp"

#include<string>
#include<vector>
#include<algorithm>
#include<functional>

#include"util/Parsing.hpp"

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

	std::string finalizeNameCompletion(std::string const & name) {
		return name + quotationMark + " ";
	}

	Completions prepend(Completions completions, std::string const & pre) {
		for (std::string & cmpl : completions) {
			cmpl = pre + cmpl;
		}
		return completions;
	}

	Completions postpend(Completions completions, std::string const & post) {
		for (std::string & cmpl : completions) {
			cmpl = cmpl + post;
		}
		return completions;
	}

	Completions nameCompletionsRaw(std::vector<std::string> const & names, CompletionFunction const & further, Context const & c, Arguments const & args) {
		Arguments newArgs;
		std::string maybeName = splitSubcommand(args, newArgs, "");
		if (maybeName.empty()) {
			return postpend(names, quotationMark + " ");
		}
		if (std::find(names.begin(), names.end(), maybeName) != names.end()) {
			return prepend(further(c, newArgs), finalizeNameCompletion(maybeName));
		}
		Completions result;
		for (std::string const & name : names) {
			if (std::equal(maybeName.begin(), maybeName.end(), name.begin())) {
				result.push_back(finalizeNameCompletion(name));
			}
		}
		return result;
	}

	CompletionFunction nameCompletions(std::vector<std::string> const & names, CompletionFunction const & further) {
		return [names, further](Context const & c, Arguments const & args) -> Completions {
			return prepend(nameCompletionsRaw(names, further, c, args), quotationMark);
		};
	}

	Completions pathCompletions(Context const & c, Arguments & args, ProjectPath & path) {
		Completions names = postpend(keyVector(c.getProject(path).getSubprojects()), "/");
		if (args.empty()) {
			return names;
		}
		std::vector<std::string> followingPath = util::tokenizePath(args.at(0));
		if (followingPath.empty()) {
			return names;
		}
		std::string nextProject = followingPath.at(0);
		if (nextProject.back() == '/') {
			if (std::find(names.begin(), names.end(), nextProject) == names.end()) {
				return Completions();
			}
			nextProject.pop_back();
			path.push_back(nextProject);
			for (unsigned int i = 0; i < followingPath.size()-1; i++) {
				followingPath[i] = followingPath[i+1];
			}
			followingPath.pop_back();
			args[0] = util::gluePath(followingPath);
			if (!followingPath.empty() && !followingPath.back().empty() && followingPath.back().back() != '/') {
				args[0].pop_back();
			}
			return prepend(pathCompletions(c, args, path), nextProject + "/");
		}
		Completions result;
		for (std::string const & name : names) {
			if (std::equal(nextProject.begin(), nextProject.end(), name.begin())) {
				result.push_back(name);
			}
		}
		return result;
	}

	CompletionFunction actionCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getActions()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction annualCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getAnnuals()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction projectCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getSubprojects()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction dependentCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getPossibleDependents()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction dependencyCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getPossibleDependencies()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction eventCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getEvents()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction habitCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getHabits()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

	CompletionFunction messCompletions(CompletionFunction const & further) {
		return [further](Context const & c, Arguments const & args) -> Completions {
			Arguments a = args;
			ProjectPath path;
			Completions result = pathCompletions(c, a, path);
			for (std::string const & cmpl : prepend(nameCompletionsRaw(keyVector(c.getProject(path).getMess()), further, c, a), util::gluePath(path)) ) {
				result.push_back(cmpl);
			}
			return prepend(result, quotationMark);
		};
	}

}
