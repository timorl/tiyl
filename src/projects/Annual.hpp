#ifndef TIYL_PROJECTS_ANNUAL_HPP
#define TIYL_PROJECTS_ANNUAL_HPP
#include<string>
#include<map>

#include"nlohmann/json.hpp"

#include"util/Dates.hpp"

namespace projects {

	using json = nlohmann::json;

	using Date = util::Date;

	class AnnualDetails {
		public:
			AnnualDetails() {}

			AnnualDetails(Date when) :	when(when) {}

			Date getWhen() const { return when; }

			void setWhen(Date const & t) { when = t; }


			int daysLeft() const;
		private:
			Date when;
	};

	void to_json(json & j, AnnualDetails const & a);

	void from_json(json const & j, AnnualDetails & a);


	using Annuals = std::map<std::string, AnnualDetails>;
	using Annual = std::pair<std::string, AnnualDetails>;

}
#endif
