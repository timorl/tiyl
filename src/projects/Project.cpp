#include"projects/Project.hpp"

namespace projects {

	void to_json(json & j, Project const & p) {
		j = {{"description", p.getDescription()}};
		if (p.getSubprojects().size()) {
			j.emplace("subprojects", p.getSubprojects());
		}
		if (p.getActions().size()) {
			j.emplace("actions", p.getActions());
		}
	}

	void from_json(json const & j, Project & p) {
		p.setDescription(j.at("description").get<std::string>());
		if (j.count("subprojects")) {
			p.setSubprojects(j.at("subprojects").get<Subprojects>());
		}
		if (j.count("actions")) {
			p.setActions(j.at("actions").get<TodoList>());
		}
	}


	void accumulateAll(Subprojects & sps, Subproject const & sp) {
		sps.emplace(sp);
		sp.second.accumulateFromSubprojects(sps, accumulateAll);
	}

	void accumulateActions(TodoList & a, Subproject const & sp) {
		TodoList const & localActions = sp.second.getActions();
		a.insert(a.end(), localActions.begin(), localActions.end());
		sp.second.accumulateFromSubprojects(a, accumulateActions);
	}

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp) {
		if (sp.second.getActions().empty()) {
			sps.emplace(sp);
		}
		sp.second.accumulateFromSubprojects(sps, accumulateNonactionable);
	}

}
