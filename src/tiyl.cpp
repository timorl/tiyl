#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<experimental/filesystem>
#include<fstream>

#include"nlohmann/json.hpp"
using json = nlohmann::json;

#include"projects/Project.hpp"
using Project = projects::Project;
using Subprojects = projects::Subprojects;
#include"projects/Todo.hpp"
using TodoList = projects::TodoList;

const std::string MESS_FILE("mess");
const std::string PROJECTS_FILE("Projects.json");

// Refactor asap unless you drop this project.
const std::string HARDCODED_DIR("/home/timorl/stuff");

int status(TodoList & mess, Project & p, std::vector<std::string>) {
	int messSize = mess.size();
	Subprojects all;
	p.accumulateFromSubprojects(all, projects::accumulateAll);
	int allSize = all.size();
	TodoList actions;
	p.accumulateFromSubprojects(actions, projects::accumulateActions);
	int actionsSize = actions.size();
	Subprojects nonactionable;
	p.accumulateFromSubprojects(nonactionable, projects::accumulateNonactionable);
	int nonactionableSize = nonactionable.size();
	std::cout << "You have a mess of size: " << messSize << std::endl;
	std::cout << "You have " << allSize << " projects." << std::endl;
	std::cout << "Among those " << nonactionableSize << " are nonactionable." << std::endl;
	std::cout << "You can take " << actionsSize << " actions." << std::endl;
	return 0;
}

using Command = std::function<int(TodoList &, Project &, std::vector<std::string>)>;

std::map<std::string, Command> runCommand = {
	{"status", status},
};

int main(int argc, char * argv[]) {
	std::experimental::filesystem::path dataDir = HARDCODED_DIR;

	std::experimental::filesystem::path messFile = dataDir;
	messFile /= MESS_FILE;
	std::fstream messFileStream(messFile);

	TodoList mess;
	messFileStream >> mess;

	std::experimental::filesystem::path projectsFile = dataDir;
	projectsFile /= PROJECTS_FILE;
	std::fstream projectsFileStream(projectsFile);

 json projects;
	std::string blas;
	projectsFileStream >> projects;
	Project life = projects;

	if (argc > 1) {
		std::vector<std::string> cmdArgs;
		for (int i = 2; i < argc; i++) {
			cmdArgs.push_back(argv[i]);
		}
		return runCommand[argv[1]](mess, life, cmdArgs);
	}

	while (std::cin.rdstate() == std::ios_base::goodbit) {
		std::cout << "tiyl> ";
		std::string input;
		std::getline(std::cin, input);
		if (input.length() == 0) {
			continue;
		}
		std::istringstream inputStream(input);
		std::string commandName;
		inputStream >> commandName;
		if (commandName.length() == 0) {
			continue;
		}
		std::vector<std::string> cmdArgs;
		std::copy(std::istream_iterator<std::string>(inputStream), std::istream_iterator<std::string>(), std::back_inserter(cmdArgs));
		if (runCommand.count(commandName)) {
			runCommand.at(commandName)(mess, life, cmdArgs);
		} else {
			std::cout << "Unknown command: " << commandName << std::endl;
		}
	}
	std::cout << "Bye!" << std::endl;
	return 0;
}
