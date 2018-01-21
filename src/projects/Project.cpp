#include"projects/Project.hpp"

namespace projects {

	Project & Project::getSubproject(std::string name) {
		return subprojects[name];
	}

	void Project::addToMess(Mess const & m) {
		mess.insert(mess.end(), m.begin(), m.end());
	}

	bool Project::isActionable() const {
		if (!actions.empty()) {
			return true;
		}
		bool result = false;
		accumulateFromSubprojects(result,
			[](bool & result, Subproject const & sp){
				return result || sp.second.isActionable();
			}
		);
		return result;
	}

	void to_json(json & j, Project const & p) {
		j = {{"description", p.getDescription()}};
		if (p.getSubprojects().size()) {
			j.emplace("subprojects", p.getSubprojects());
		}
		if (p.getActions().size()) {
			j.emplace("actions", p.getActions());
		}
		if (p.getMess().size()) {
			j.emplace("mess", p.getMess());
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
		if (j.count("mess")) {
			p.setMess(j.at("mess").get<Mess>());
		}
	}


	void accumulateAll(Subprojects & sps, Subproject const & sp) {
		sps.emplace(sp);
		sp.second.accumulateFromSubprojects(sps, accumulateAll);
	}

	void accumulateMess(Mess & m, Subproject const & sp) {
		Mess const & localMess = sp.second.getMess();
		m.insert(m.end(), localMess.begin(), localMess.end());
		sp.second.accumulateFromSubprojects(m, accumulateMess);
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
