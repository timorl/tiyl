#include"util/Config.hpp"

#include<fstream>
#include<iostream>
#include<cstdlib>

namespace util {

	void Config::loadFromFile(path const & theFile) {
		std::ifstream stream(theFile);
		if (stream.fail()) {
			std::cout << "The configuration file " << theFile << " does not exist, creating and filling with default values." << std::endl;
			dataDir = defaultDataDir();
			projectsFile = defaultProjectsFile();
			std::experimental::filesystem::create_directories(theFile.parent_path());
			std::ofstream writeStream(theFile);
			json j = *this;
			writeStream << std::setw(1) << j << std::endl;
			stream = std::ifstream(theFile);
		}
		json j;
		stream >> j;
		from_json(j, *this);
	}

	path Config::defaultDataDir() {
		path result(std::getenv("HOME"));
		return result/".local/share/tiyl";
	}

	path Config::defaultProjectsFile() { return path("Projects.json"); }


	void to_json(json & j, Config const & c) {
		j = {
			{"dataDir", c.getDataDir().string()},
			{"projectsFile", c.getProjectsFile().string()},
		};
	}

	void from_json(json const & j, Config & c) {
		c.setDataDir(j.at("dataDir").get<std::string>());
		c.setProjectsFile(j.at("projectsFile").get<std::string>());
	}

}
