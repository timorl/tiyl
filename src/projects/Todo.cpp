#include"projects/Todo.hpp"

namespace projects {

	std::istream & operator>>(std::istream & is, TodoList & l) {
		Todo item;
		while (std::getline(is, item)) {
			if (item.length()) {
				l.push_back(item);
			}
		}
		return is;
	}

}
