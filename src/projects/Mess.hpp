#ifndef TIYL_PROJECTS_MESS_HPP
#define TIYL_PROJECTS_MESS_HPP
#include<string>
#include<set>
#include<istream>

namespace projects {

	class Mess : public std::set<std::string> {};

	std::istream & operator>>(std::istream & is, Mess & l);

}
#endif
