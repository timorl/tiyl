#ifndef TIYL_UTIL_CONFIG_HPP
#define TIYL_UTIL_CONFIG_HPP
#include<string>
#include<experimental/filesystem>

#include"nlohmann/json.hpp"

namespace util {

	using path = std::experimental::filesystem::path;
	using json = nlohmann::json;

	class Config {
		public:
			Config() {}

			path const & getDataDir() const { return dataDir; }

			path getProjectsFile() const { return dataDir/projectsFile; }

			void setDataDir(std::string const & dd) { dataDir = dd; }

			void setProjectsFile(std::string const & pf) { projectsFile = pf; }


			void loadFromFile(path const & cf);


			static path defaultDataDir();

			static path defaultProjectsFile();
		private:
			path dataDir;
			path projectsFile;
	};

	void to_json(json & j, Config const & c);

	void from_json(json const & j, Config & c);

}
#endif
