#include"projects/Event.hpp"

namespace projects {

	void EventDetails::updateDependencies(std::set<std::string> possibleDependencies) {
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

	int EventDetails::daysLeft() const {
		return -util::daysSince(when);
	}


	void to_json(json & j, EventDetails const & e) {
		j = {{"when", util::dateToString(e.getWhen())}};
		if (!e.getDependencies().empty()) {
			j.emplace("deps", e.getDependencies());
		}
	}

	void from_json(json const & j, EventDetails & e) {
		e.setWhen(util::stringToDate(j.at("when").get<std::string>()));
		if (j.count("deps")) {
			e.setDependencies(j.at("deps").get<std::set<std::string>>());
		}
	}


}
