#include"database/Files.hpp"

#include<fstream>

#include"nlohmann/json.hpp"

namespace database {

	using json = nlohmann::json;

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
