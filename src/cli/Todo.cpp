#include"cli/Todo.hpp"

#include<iostream>

#include"cli/Pretty.hpp"

namespace cli {

	void printTodoName(std::string const & name, Todo const &) {
		std::cout << name << std::endl;
	}

	void printTodoNames(TodoList const & todos) {
		if (todos.empty()) {
			std::cout << lessVisible("No todos.") << std::endl;
			return;
		}
		std::cout << brightWhite("Todos:") << std::endl;
		for (auto const & t : todos) {
			std::cout << " ";
			printTodoName(t.first, t.second);
		}
	}

	int todoDone(Context & c, std::vector<std::string> const & args) {
		TodoList const & todos = c.getProject().getTodos();
		if (todos.empty()) {
			std::cout << "No todos." << std::endl;
			return 2;
		}
		std::vector<std::string> names;
		for (auto const & t : todos) {
			names.push_back(t.first);
		}
		int todoId;
		if ( !args.empty() ) {
			todoId = decodeChoice(names, "todo", args[0]);
		} else {
			todoId = requestChoice(names, "todo");
		}
		if (todoId == -1) {
			return 1;
		}
		c.delTodo(names.at(todoId));
		return 0;
	}

	Todo buildTodo(std::vector<std::string> const & args) {
		std::string name;
		if ( !args.empty() ) {
			name = args[0];
		} else {
			std::cout << "Name: ";
			std::cin >> name;
		}
		return Todo(name);
	}

	int todoAdd(Context & c, std::vector<std::string> const & args) {
		if ( !c.addTodo( buildTodo(args) ) ) {
			std::cout << "Todo name conflict." << std::endl;
			return 1;
		}
		return 0;
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
		for (auto const & t : todos) {
			names.push_back(t.first);
		}
		int todoId;
		if ( !args.empty() ) {
			todoId = decodeChoice(names, "todo", args[0]);
		} else {
			todoId = requestChoice(names, "todo");
		}
		if (todoId == -1) {
			return 1;
		}
		std::string todoName = names.at(todoId);
		printTodoName(todoName, todos.at(todoName));
		return 0;
	}

	int todo(Context & c, std::vector<std::string> const & args) {
		std::vector<std::string> newArgs;
		std::string subcommand = splitSubcommand(args, newArgs, "list");
		return singleCommand(todoCommands, c, subcommand, newArgs);
	}

}
