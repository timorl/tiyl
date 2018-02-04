#ifndef TIYL_PROJECTS_EVENT_HPP
#define TIYL_PROJECTS_EVENT_HPP
#include<string>
#include<map>

#include"nlohmann/json.hpp"

#include"util/Dates.hpp"

namespace projects {

	using json = nlohmann::json;

	using Date = util::Date;

	class EventDetails {
		public:
			EventDetails() {}

			EventDetails(Date when) :	when(when) {}

			Date getWhen() const { return when; }

			void setWhen(Date const & t) { when = t; }


			int daysLeft() const;
		private:
			Date when;
	};

	void to_json(json & j, EventDetails const & e);

	void from_json(json const & j, EventDetails & e);


	using Events = std::map<std::string, EventDetails>;
	using Event = std::pair<std::string, EventDetails>;

}
#endif
