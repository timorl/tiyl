#include"projects/Annual.hpp"

namespace projects {

	void AnnualDetails::updateDependencies(std::set<std::string> possibleDependencies) {
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

	int AnnualDetails::daysLeft() const {
		return -util::daysSince(when);
	}


	void to_json(json & j, AnnualDetails const & a) {
		j = {{"when", util::annualToString(a.getWhen())}};
		if (!a.getDependencies().empty()) {
			j.emplace("deps", a.getDependencies());
		}
	}

	void from_json(json const & j, AnnualDetails & a) {
		a.setWhen(util::stringToAnnual(j.at("when").get<std::string>()));
		if (j.count("deps")) {
			a.setDependencies(j.at("deps").get<std::set<std::string>>());
		}
	}

}
