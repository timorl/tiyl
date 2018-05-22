#ifndef TIYL_CLI_COMPLETIONS_HPP
#define TIYL_CLI_COMPLETIONS_HPP

#include"cli/Context.hpp"
#include"cli/Command.hpp"
#include"util/Dates.hpp"

namespace cli {

	Completions noCompletions(Context const &, Arguments const &);

	CompletionFunction subcommandCompletions(Commands const & subcommands);

	CompletionFunction nameCompletions(std::vector<std::string> const & names, CompletionFunction const & further);

	CompletionFunction actionCompletions(CompletionFunction const & further);

	CompletionFunction annualCompletions(CompletionFunction const & further);

	CompletionFunction projectCompletions(CompletionFunction const & further);

	CompletionFunction dependentCompletions(CompletionFunction const & further);

	CompletionFunction dependencyCompletions(CompletionFunction const & further);

	CompletionFunction eventCompletions(CompletionFunction const & further);

	CompletionFunction habitCompletions(CompletionFunction const & further);

	CompletionFunction messCompletions(CompletionFunction const & further);

}
#endif
