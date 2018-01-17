#ifndef TIYL_PROJECTS_TODO_HPP
#define TIYL_PROJECTS_TODO_HPP
#include<string>
#include<vector>
#include<istream>

namespace projects {

	using Todo = std::string;

	class TodoList : public std::vector<Todo> {};

	std::istream & operator>>(std::istream & is, TodoList & l);

}
#endif
