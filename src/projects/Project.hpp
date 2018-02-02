#ifndef TIYL_PROJECTS_PROJECT_HPP
#define TIYL_PROJECTS_PROJECT_HPP
#include<string>
#include<map>
#include<vector>

#include"nlohmann/json.hpp"

#include"projects/Mess.hpp"
#include"projects/Action.hpp"

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

			Mess const & getMess() const { return mess; }

			bool isFrozen() const { return frozen; }

			void setDescription(std::string const & d) { description = d; }

			void setSubprojects(Subprojects const & s) { subprojects = s; }

			void setActions(Actions const & a) { actions = a; }

			void setMess(Mess const & m) { mess = m; }

			void setFrozen(bool f) { frozen = f; }


			void addToMess(Mess const & m);

			void addMess(std::string const & name);

			void delMess(std::string const & name);

			bool addAction(Action && t);

			void delAction(std::string const & name);

			bool addSubproject(Subproject && s);

			void delSubproject(std::string const & name);

			Project & getSubproject(std::string name);


			bool isActionable() const;

			bool empty() const;


			template<typename T, typename Fun>
			void accumulateFromSubprojects(T & result, Fun accumulator) const {
				for (Subproject const & sp : getSubprojects()) {
					accumulator(result, sp);
				}
			}
		private:
			std::string description;
			Subprojects subprojects;
			Actions actions;
			Mess mess;
			bool frozen;
	};

	void to_json(json & j, Project const & p);

	void from_json(json const & j, Project & p);

	void accumulateAll(Subprojects & sps, Subproject const & sp);

	void accumulateMess(Mess & m, Subproject const & sp);

	void accumulateActions(Actions & a, Subproject const & sp);

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp);

}
#endif
