#include"projects/Project.hpp"

namespace projects {

	void Project::addToMess(Mess const & m) {
		mess.insert(m.begin(), m.end());
	}

	void Project::addMess(std::string const & name) {
		mess.insert(name);
	}

	void Project::delMess(std::string const & name) {
		mess.erase(name);
	}

	bool Project::addAction(Action && a) {
		return actions.insert(std::move(a)).second;
	}

	void Project::delAction(std::string const & name) {
		actions.erase(name);
	}

	bool Project::addSubproject(Subproject && s) {
		return subprojects.insert(std::move(s)).second;
	}

	void Project::delSubproject(std::string const & name) {
		subprojects.erase(name);
	}

	Project & Project::getSubproject(std::string name) {
		return subprojects[name];
	}


	bool Project::isActionable() const {
		if (!actions.empty()) {
			return true;
		}
		bool result = false;
		accumulateFromSubprojects(result,
			[](bool & result, Subproject const & sp){
				result = result || sp.second.isActionable();
			}
		);
		return result;
	}

	bool Project::empty() const {
		return subprojects.empty() && actions.empty() && mess.empty();
	}


	void to_json(json & j, Project const & p) {
		j = {{"description", p.getDescription()}};
		if (!p.getSubprojects().empty()) {
			j.emplace("subprojects", p.getSubprojects());
		}
		if (!p.getActions().empty()) {
			j.emplace("actions", p.getActions());
		}
		if (!p.getMess().empty()) {
			j.emplace("mess", p.getMess());
		}
		if (p.isFrozen()) {
			j.emplace("frozen", p.isFrozen());
		}
	}

	void from_json(json const & j, Project & p) {
		p.setDescription(j.at("description").get<std::string>());
		if (j.count("subprojects")) {
			p.setSubprojects(j.at("subprojects").get<Subprojects>());
		}
		if (j.count("actions")) {
			p.setActions(j.at("actions").get<Actions>());
		}
		if (j.count("mess")) {
			p.setMess(j.at("mess").get<Mess>());
		}
		if (j.count("frozen")) {
			p.setFrozen(j.at("frozen").get<bool>());
		} else {
			p.setFrozen(false);
		}
	}


	void accumulateAll(Subprojects & sps, Subproject const & sp) {
		sps.emplace(sp);
		sp.second.accumulateFromSubprojects(sps, accumulateAll);
	}

	void accumulateMess(Mess & m, Subproject const & sp) {
		Mess const & localMess = sp.second.getMess();
		m.insert(localMess.begin(), localMess.end());
		sp.second.accumulateFromSubprojects(m, accumulateMess);
	}

	void accumulateActions(Actions & a, Subproject const & sp) {
		Actions const & localActions = sp.second.getActions();
		a.insert(localActions.begin(), localActions.end());
		sp.second.accumulateFromSubprojects(a, accumulateActions);
	}

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp) {
		if (sp.second.getActions().empty()) {
			sps.emplace(sp);
		}
		sp.second.accumulateFromSubprojects(sps, accumulateNonactionable);
	}

}
