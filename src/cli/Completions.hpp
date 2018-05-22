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

}
#endif
