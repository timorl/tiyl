#include"projects/Action.hpp"

namespace projects {

	void ActionDetails::updateDependencies(std::set<std::string> possibleDependencies) {
		std::set<std::string> toErase;
		for (std::string const & dep : dependencies) {
			if (!possibleDependencies.count(dep)) {
				toErase.insert(dep);
			}
		}
		for (std::string const & te : toErase) {
			dependencies.erase(te);
		}
	}


	void to_json(json & j, ActionDetails const & a) {
		j = {{"duration", a.getDuration()}};
		if (!a.getDependencies().empty()) {
			j.emplace("deps", a.getDependencies());
		}
	}

	void from_json(json const & j, ActionDetails & a) {
		if (j.count("duration")) {
			a.setDuration(j.at("duration").get<int>());
		}
		if (j.count("deps")) {
			a.setDependencies(j.at("deps").get<std::set<std::string>>());
		}
	}


}
