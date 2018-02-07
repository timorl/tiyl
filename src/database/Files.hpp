#ifndef TIYL_DATABASE_FILES_HPP
#define TIYL_DATABASE_FILES_HPP
#include<experimental/filesystem>

#include"projects/Mess.hpp"
#include"projects/Project.hpp"

namespace database {
	
	using path = std::experimental::filesystem::path;

	using Mess = projects::Mess;
	using Project = projects::Project;

	Project readProject(path const & p);

	void writeProject(path const & p, Project const & project);

}
#endif
