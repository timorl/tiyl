#include"projects/Annual.hpp"

namespace projects {

	int AnnualDetails::daysLeft() const {
		return -util::daysSince(when);
	}

	void to_json(json & j, AnnualDetails const & a) {
		j = {
			{"when", util::annualToString(a.getWhen())},
		};
	}

	void from_json(json const & j, AnnualDetails & a) {
		a.setWhen(util::stringToAnnual(j.at("when").get<std::string>()));
	}


}
