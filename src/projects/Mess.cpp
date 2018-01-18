#include"projects/Mess.hpp"

namespace projects {

	std::istream & operator>>(std::istream & is, Mess & l) {
		std::string item;
		while (std::getline(is, item)) {
			if (item.length()) {
				l.push_back(item);
			}
		}
		return is;
	}

}
