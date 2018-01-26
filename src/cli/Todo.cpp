#include"cli/Todo.hpp"

#include<iostream>

#include"cli/Pretty.hpp"

namespace cli {

	void printTodoName(Todo const & t) {
		std::cout << t << std::endl;
	}

	void printTodoNames(TodoList const & todos) {
		if (todos.empty()) {
			std::cout << lessVisible("No todos.") << std::endl;
			return;
		}
		std::cout << brightWhite("Todos:") << std::endl;
		for (Todo const & t : todos) {
			std::cout << " ";
			printTodoName(t);
		}
	}

	int todoList(Context & c, std::vector<std::string> const &) {
		TodoList const & todos = c.getProject().getTodos();
		printTodoNames(todos);
		return 0;
	}

	int todoShow(Context & c, std::vector<std::string> const & args) {
		TodoList const & todos = c.getProject().getTodos();
		if (todos.empty()) {
			std::cout << "No todos." << std::endl;
			return 2;
		}
		std::vector<std::string> names;
		for (Todo const & t : todos) {
			names.push_back(t);
		}
		std::string todoName;
		if ( !args.empty() ) {
			todoName = decodeChoice(names, "todo", args[0]);
		} else {
			todoName = requestChoice(names, "todo");
		}
		if (todoName.empty()) {
			return 1;
		}
		printTodoName(todoName);
		return 0;
	}

	int todo(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(todoCommands, c, subcommand, newArgs);
	}

}
