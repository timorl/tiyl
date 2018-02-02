#include"projects/Action.hpp"

namespace projects {


	void to_json(json & j, ActionDetails const & a) {
		j = {{"duration", a.getDuration()}};
	}

	void from_json(json const & j, ActionDetails & a) {
		if (j.count("duration")) {
			a.setDuration(j.at("duration").get<int>());
		}
	}


}
