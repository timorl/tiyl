#ifndef TIYL_PROJECTS_ACTION_HPP
#define TIYL_PROJECTS_ACTION_HPP
#include<string>
#include<map>

#include"nlohmann/json.hpp"

namespace projects {

	using json = nlohmann::json;

	class ActionDetails {
		public:
			ActionDetails(int duration = 0) : duration(duration) {}

			int getDuration() const { return duration; }

			void setDuration(int d) { duration = d; }
		private:
			int duration;
	};

	void to_json(json & j, ActionDetails const & a);

	void from_json(json const & j, ActionDetails & a);


	using Actions = std::map<std::string, ActionDetails>;
	using Action = std::pair<std::string, ActionDetails>;

}
#endif
