#include"database/Files.hpp"

#include<fstream>

#include"nlohmann/json.hpp"

namespace database {

	using json = nlohmann::json;

	Mess readMess(path const & p) {
		Mess m;
		std::ifstream stream(p);
		stream >> m;
		return m;
	}

	void clearMess(path const & p) {
		std::ofstream stream(p, std::ofstream::trunc);
	}

	Project readProject(path const & p) {
		std::ifstream stream(p);
		json j;
		stream >> j;
		return j;
	}

	void writeProject(path const & p, Project const & project) {
		json j = project;
		std::ofstream stream(p, std::ofstream::trunc);
		stream << std::setw(1) << j << std::endl;
	}

}
