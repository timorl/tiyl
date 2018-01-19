#ifndef TIYL_PROJECTS_PROJECT_HPP
#define TIYL_PROJECTS_PROJECT_HPP
#include<string>
#include<map>
#include<vector>

#include"nlohmann/json.hpp"

#include"projects/Todo.hpp"

namespace projects {

	using json = nlohmann::json;

	class Project;

	using Subprojects = std::map<std::string, Project>;
	using Subproject = std::pair<std::string, Project>;

	class Project {
		public:
			Project() {}

			std::string const & getDescription() const { return description; }

			Subprojects const & getSubprojects() const { return subprojects; }

			TodoList const & getActions() const { return actions; }

			void setDescription(std::string const & d) { description = d; }

			void setSubprojects(Subprojects const & s) { subprojects = s; }

			void setActions(TodoList const & a) { actions = a; }

			Project & getSubproject(std::string name);

			bool isActionable() const;

			template<typename T, typename Fun>
			void accumulateFromSubprojects(T & result, Fun accumulator) const {
				for (Subproject const & sp : getSubprojects()) {
					accumulator(result, sp);
				}
			}
		private:
			std::string description;
			Subprojects subprojects;
			TodoList actions;
	};

	void to_json(json & j, Project const & p);

	void from_json(json const & j, Project & p);

	void accumulateAll(Subprojects & sps, Subproject const & sp);

	void accumulateActions(TodoList & a, Subproject const & sp);

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp);

}
#endif