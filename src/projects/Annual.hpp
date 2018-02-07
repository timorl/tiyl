#ifndef TIYL_PROJECTS_ANNUAL_HPP
#define TIYL_PROJECTS_ANNUAL_HPP
#include<string>
#include<map>
#include<set>

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

			std::set<std::string> const & getDependencies() const { return dependencies; }

			void setDependencies(std::set<std::string> const & d) { dependencies = d; }

			void addDependency(std::string dependency) { dependencies.insert(dependency); }

			void updateDependencies(std::set<std::string> possibleDependencies);


			int daysLeft() const;
		private:
			Date when;
			std::set<std::string> dependencies;
	};

	void to_json(json & j, AnnualDetails const & a);

	void from_json(json const & j, AnnualDetails & a);


	using Annuals = std::map<std::string, AnnualDetails>;
	using Annual = std::pair<std::string, AnnualDetails>;

}
#endif
