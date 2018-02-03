#include"projects/Habit.hpp"

namespace projects {

	bool HabitDetails::due() const {
		return util::daysSince(lastDone) > minimalBreak-1;
	}

	bool HabitDetails::pastDue() const {
		return util::daysSince(lastDone) > maximalBreak-1;
	}

	void HabitDetails::done() {
		lastDone = std::chrono::system_clock::now();
	}

	void to_json(json & j, HabitDetails const & h) {
		j = {
			{"minimalBreak", h.getMinBreak()},
			{"maximalBreak", h.getMaxBreak()},
			{"lastDone", util::dateToString(h.getLastDone())},
		};
	}

	void from_json(json const & j, HabitDetails & h) {
		h.setMinBreak(j.at("minimalBreak").get<int>());
		h.setMaxBreak(j.at("maximalBreak").get<int>());
		h.setLastDone(util::stringToDate(j.at("lastDone").get<std::string>()));
	}


}
