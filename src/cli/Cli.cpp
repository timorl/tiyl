#include"cli/Cli.hpp"

#include<iostream>
#include<memory>

#include"linenoise/linenoise.h"

namespace cli {

	std::string getSingleToken(std::string const & input, unsigned long long & start) {
		while (start < input.length() && input[start] == ' ') {
			start++;
		}
		if (start >= input.length()) {
			return "";
		}
		std::string result;
		unsigned long long end;
		if (input[start] == '"') {
			start++;
			if (start >= input.length()) {
				return "";
			}
			end = input.find('"', start);
			if (end == std::string::npos) {
				end = input.length()-1;
			}
		} else {
			end = input.find(' ', start);
			if (end == std::string::npos) {
				end = input.length();
			}
		}
		result = input.substr(start, end - start);
		start = end;
		return result;
	}

	Arguments tokenize(std::string const & input) {
		Arguments result;
		unsigned long long position = 0;
		while (position < input.length()) {
			std::string token = getSingleToken(input, position);
			if (token.length() != 0) {
				result.push_back(token);
			}
		}
		return result;
	}

	std::function<void(const char *, linenoiseCompletions *)> completionForContext(Context const & c) {
		return [&c](const char * buf, linenoiseCompletions * lc) {
			Arguments tokenized = tokenize(buf);
			Completions result = subcommandCompletions(commands)(c, tokenized);
			for (std::string const & cmpl : result) {
				linenoiseAddCompletion(lc, cmpl.c_str());
			}
		};
	}
	
	std::function<void(const char *, linenoiseCompletions *)> currentCompletion;

	void currentCompletionWrapper(const char * buf, linenoiseCompletions * lc) {
		currentCompletion(buf, lc);
	}

	void initLinenoise(Context const & c) {
		linenoiseHistorySetMaxLen(128);
		currentCompletion = completionForContext(c);
		linenoiseSetCompletionCallback(currentCompletionWrapper);
	}

	std::string currentPrompt(Context const & c) {
		return c.getCurrentName() + "> ";
	}

	bool prompt(Context const & c, std::string & input) {
		std::unique_ptr<char, decltype(&linenoiseFree)> lineRead(
				linenoise(currentPrompt(c).c_str()),
				&linenoiseFree);
		if (lineRead) {
			input = lineRead.get();
			linenoiseHistoryAdd(lineRead.get());
			return true;
		}
		return false;
	}

	void commandLine(Context & c, std::function<void(Context &)> save) {
		initLinenoise(c);
		std::string input;
		while (prompt(c, input)) {
			Arguments tokenized = tokenize(input);
			if (tokenized.empty()) {
				continue;
			}
			Arguments args;
			std::string name = splitSubcommand(tokenized, args, "");
			c.setLastResult(singleCommand(commands, c, name, args));
			save(c);
		}
		std::cout << "Bye!" << std::endl;
	}

}
