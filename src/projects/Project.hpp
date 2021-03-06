#ifndef TIYL_PROJECTS_PROJECT_HPP
#define TIYL_PROJECTS_PROJECT_HPP
#include<string>
#include<map>
#include<vector>
#include<set>

#include"nlohmann/json.hpp"

#include"projects/Mess.hpp"
#include"projects/Action.hpp"
#include"projects/Habit.hpp"
#include"projects/Event.hpp"
#include"projects/Annual.hpp"

namespace projects {

	using json = nlohmann::json;

	class Project;

	using Subprojects = std::map<std::string, Project>;
	using Subproject = std::pair<std::string, Project>;

	class Project {
		public:
			Project() : frozen(false) {}

			Project(std::string description) : description(description), frozen(false) {}

			std::string const & getDescription() const { return description; }

			Subprojects const & getSubprojects() const { return subprojects; }

			Actions const & getActions() const { return actions; }

			Habits const & getHabits() const { return habits; }

			Events const & getEvents() const { return events; }

			Annuals const & getAnnuals() const { return annuals; }

			Mess const & getMess() const { return mess; }

			bool isFrozen() const { return frozen; }

			void setDescription(std::string const & d) { description = d; }

			void setSubprojects(Subprojects const & s) { subprojects = s; }

			void setActions(Actions const & a) { actions = a; }

			void setHabits(Habits const & h) { habits = h; }

			void setEvents(Events const & e) { events = e; }

			void setAnnuals(Annuals const & a) { annuals = a; }

			void setMess(Mess const & m) { mess = m; }

			void setFrozen(bool f) { frozen = f; }


			void addToMess(Mess const & m);

			void addMess(std::string const & name);

			void delMess(std::string const & name);

			bool addAction(Action && t);

			void delAction(std::string const & name);

			bool addHabit(Habit && t);

			void doHabit(std::string const & name);

			void delHabit(std::string const & name);

			bool addEvent(Event && t);

			void delEvent(std::string const & name);

			bool addAnnual(Annual && t);

			void delAnnual(std::string const & name);

			bool addSubproject(Subproject && s);

			void delSubproject(std::string const & name);

			bool addDependency(std::string what, std::string onWhat);

			void updateDependencies();

			Project & getSubproject(std::string name);


			std::set<std::string> getPossibleDependents() const;

			std::set<std::string> getPossibleDependencies() const;

			bool isActionable() const;

			bool empty() const;


			template<typename T, typename Fun>
			void accumulateFromSubprojects(T & result, Fun accumulator) const {
				for (Subproject const & sp : getSubprojects()) {
					if (!sp.second.isFrozen()) {
						accumulator(result, sp);
					}
				}
			}
		private:
			std::string description;
			Subprojects subprojects;
			Actions actions;
			Habits habits;
			Events events;
			Annuals annuals;
			Mess mess;
			bool frozen;
	};

	void to_json(json & j, Project const & p);

	void from_json(json const & j, Project & p);

	void accumulateAll(Subprojects & sps, Subproject const & sp);

	using ProjectAccumulator = std::function<void(Subprojects &, Subproject const &)>;

	void accumulateMess(Mess & m, Subproject const & sp);

	using MessAccumulator = std::function<void(Mess &, Subproject const &)>;

	void accumulateActions(Actions & a, Subproject const & sp);

	using ActionAccumulator = std::function<void(Actions &, Subproject const &)>;

	void accumulateHabits(Habits & h, Subproject const & sp);

	using HabitAccumulator = std::function<void(Habits &, Subproject const &)>;

	void accumulateEvents(Events & e, Subproject const & sp);

	using EventAccumulator = std::function<void(Events &, Subproject const &)>;

	void accumulateAnnuals(Annuals & a, Subproject const & sp);

	using AnnualAccumulator = std::function<void(Annuals &, Subproject const &)>;

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp);

}
#endif
