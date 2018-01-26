#ifndef TIYL_CLI_TODO_HPP
#define TIYL_CLI_TODO_HPP
#include<string>
#include<map>

#include"cli/Utils.hpp"
#include"cli/Context.hpp"
#include"projects/Todo.hpp"

namespace cli {

	using Todo = projects::Todo;
	using TodoList = projects::TodoList;

	void printTodoNames(TodoList const & todos);

	int todoList(Context & c, std::vector<std::string> const &);

	int todoShow(Context & c, std::vector<std::string> const & args);

	int todo(Context & c, std::vector<std::string> const & args);

	const std::map<std::string, Command> todoCommands = {
		{"list", todoList},
		{"show", todoShow},
	};

}
#endif
