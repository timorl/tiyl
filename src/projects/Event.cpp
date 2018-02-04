#include"projects/Event.hpp"

namespace projects {

	int EventDetails::daysLeft() const {
		return -util::daysSince(when);
	}

	void to_json(json & j, EventDetails const & e) {
		j = {
			{"when", util::dateToString(e.getWhen())},
		};
	}

	void from_json(json const & j, EventDetails & e) {
		e.setWhen(util::stringToDate(j.at("when").get<std::string>()));
	}


}
