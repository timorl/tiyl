#include<iostream>
#include<string>
#include<vector>
#include<experimental/filesystem>

#include"database/Files.hpp"
#include"cli/Context.hpp"
#include"cli/Cli.hpp"

using Context = cli::Context;

const std::string PROJECTS_FILE("Projects.json");

// Refactor asap unless you drop this project.
const std::string HARDCODED_DIR("/home/timorl/stuff");

int main(int argc, char * argv[]) {
	std::experimental::filesystem::path dataDir = HARDCODED_DIR;

	std::experimental::filesystem::path projectsFile = dataDir;
	projectsFile /= PROJECTS_FILE;

	Context context(database::readProject(projectsFile));

	std::function<void(Context &)> save = [projectsFile](Context & context) {
		if (context.modified()) {
			database::writeProject(projectsFile, context.getMainProject());
			context.resetModified();
		}
	};

	if (argc > 1) {
		cli::Arguments cmdArgs;
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
