#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<experimental/filesystem>

#include"projects/Project.hpp"
#include"projects/Todo.hpp"
#include"projects/Mess.hpp"
#include"database/Files.hpp"
#include"cli/Context.hpp"
#include"cli/Cli.hpp"

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

	std::experimental::filesystem::path projectsFile = dataDir;
	projectsFile /= PROJECTS_FILE;

	Context context(database::readProject(projectsFile));

	std::function<void(Context &)> save = [projectsFile](Context & context) {
		if (context.modified()) {
			database::writeProject(projectsFile, context.getMainProject());
			context.resetModified();
		}
	};

	context.addMess(database::readMess(messFile));
	save(context);
	database::clearMess(messFile);

	if (argc > 1) {
		std::vector<std::string> cmdArgs;
		for (int i = 2; i < argc; i++) {
			cmdArgs.push_back(argv[i]);
		}
		int result = cli::singleCommand(cli::commands, context, argv[1], cmdArgs);
		save(context);
		return result;
	}

	cli::commandLine(context, save);
	return 0;
}
