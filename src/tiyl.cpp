#include<iostream>
#include<string>
#include<vector>
#include<experimental/filesystem>

#include"database/Files.hpp"
#include"util/Config.hpp"
#include"cli/Context.hpp"
#include"cli/Cli.hpp"

using Config = util::Config;
using Context = cli::Context;
using Project = projects::Project;

const std::string configFileSansHome(".config/tiyl/config.json");

int main(int argc, char * argv[]) {
	Config cfg;
	std::experimental::filesystem::path configFile(std::getenv("HOME"));
	configFile /= configFileSansHome;
	cfg.loadFromFile(configFile);

	std::experimental::filesystem::path projectsFile = cfg.getProjectsFile();
	if (!std::experimental::filesystem::exists(projectsFile)) {
		Project defaultLife;
		defaultLife.setDescription("This is your life.");
		std::experimental::filesystem::create_directories(projectsFile.parent_path());
		database::writeProject(projectsFile, defaultLife);
	}

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
