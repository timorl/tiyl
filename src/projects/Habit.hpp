#ifndef TIYL_PROJECTS_HABIT_HPP
#define TIYL_PROJECTS_HABIT_HPP
#include<string>
#include<map>

#include"nlohmann/json.hpp"

#include"util/Dates.hpp"

namespace projects {

	using json = nlohmann::json;

	using Date = util::Date;

	class HabitDetails {
		public:
			HabitDetails() {}

			HabitDetails(int minimalBreak, int maximalBreak, Date lastDone) :
				minimalBreak(minimalBreak),
				maximalBreak(maximalBreak),
				lastDone(lastDone) {}

			int getMinBreak() const { return minimalBreak; }

			int getMaxBreak() const { return maximalBreak; }

			Date getLastDone() const { return lastDone; }

			void setMinBreak(int d) { minimalBreak = d; }

			void setMaxBreak(int d) { maximalBreak = d; }

			void setLastDone(Date const & t) { lastDone = t; }


			bool due() const;

			bool pastDue() const;

			void done();
		private:
			int minimalBreak;
			int maximalBreak;
			Date lastDone;
	};

	void to_json(json & j, HabitDetails const & h);

	void from_json(json const & j, HabitDetails & h);


	using Habits = std::map<std::string, HabitDetails>;
	using Habit = std::pair<std::string, HabitDetails>;

}
#endif
