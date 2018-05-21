#ifndef TIYL_CLI_COMMAND_HPP
#define TIYL_CLI_COMMAND_HPP
#include<string>
#include<vector>
#include<map>

#include"cli/Context.hpp"

namespace cli {

	using Arguments = std::vector<std::string>;
	using Completions = std::vector<std::string>;

	using CommandFunction = std::function<int(Context &, Arguments const &)>;
	using CompletionFunction = std::function<Completions(Context const &, Arguments const &)>;

	class Command {
		public:
			Command(CommandFunction cmd, CompletionFunction cmpl) :
				 cmd(cmd),
					cmpl(cmpl) {}
			int operator()(Context & c, Arguments const & args) const {return cmd(c, args);}
			Completions completions(Context const & c, Arguments const & args) const {return cmpl(c, args);}
		private:
			CommandFunction cmd;
			CompletionFunction cmpl;
	};

 using Commands = std::map<std::string, Command>;

}
#endif
