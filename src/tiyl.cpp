#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<experimental/filesystem>
#include<fstream>

#include"nlohmann/json.hpp"

#include"projects/Project.hpp"
#include"projects/Todo.hpp"
#include"projects/Mess.hpp"
#include"cli/Context.hpp"
#include"cli/Cli.hpp"

using json = nlohmann::json;

using Project = projects::Project;
using Subprojects = projects::Subprojects;
using TodoList = projects::TodoList;
using Mess = projects::Mess;
using Context = cli::Context;

const std::string MESS_FILE("mess");
const std::string PROJECTS_FILE("Projects.json");

// Refactor asap unless you drop this project.
const std::string HARDCODED_DIR("/home/timorl/stuff");

int main(int argc, char * argv[]) {
	std::experimental::filesystem::path dataDir = HARDCODED_DIR;

	std::experimental::filesystem::path messFile = dataDir;
	messFile /= MESS_FILE;
	std::fstream messFileStream(messFile);

	Mess mess;
	messFileStream >> mess;

	std::experimental::filesystem::path projectsFile = dataDir;
	projectsFile /= PROJECTS_FILE;
	std::fstream projectsFileStream(projectsFile);

 json projects;
	std::string blas;
	projectsFileStream >> projects;

	Context context(projects, std::move(mess));

	if (argc > 1) {
		std::vector<std::string> cmdArgs;
		for (int i = 2; i < argc; i++) {
			cmdArgs.push_back(argv[i]);
		}
		return cli::singleCommand(context, argv[1], cmdArgs);
	}

	cli::commandLine(context);
	return 0;
}
