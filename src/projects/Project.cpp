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

	bool Project::addHabit(Habit && h) {
		return habits.insert(std::move(h)).second;
	}

	void Project::doHabit(std::string const & name) {
		habits[name].done();
	}

	void Project::delHabit(std::string const & name) {
		habits.erase(name);
	}

	bool Project::addEvent(Event && e) {
		return events.insert(std::move(e)).second;
	}

	void Project::delEvent(std::string const & name) {
		events.erase(name);
	}

	bool Project::addAnnual(Annual && a) {
		return annuals.insert(std::move(a)).second;
	}

	void Project::delAnnual(std::string const & name) {
		annuals.erase(name);
	}

	bool Project::addSubproject(Subproject && s) {
		return subprojects.insert(std::move(s)).second;
	}

	void Project::delSubproject(std::string const & name) {
		subprojects.erase(name);
	}

	bool Project::addDependency(std::string what, std::string onWhat) {
		std::set<std::string> possibleDependencies = getPossibleDependencies();
		if (!possibleDependencies.count(onWhat)) {
			return false;
		}
		if (actions.count(what)) {
			actions[what].addDependency(onWhat);
			return true;
		}
		if (events.count(what)) {
			events[what].addDependency(onWhat);
			return true;
		}
		if (annuals.count(what)) {
			annuals[what].addDependency(onWhat);
			return true;
		}
		return false;
	}

	void Project::updateDependencies() {
		std::set<std::string> possibleDependencies = getPossibleDependencies();
		for (auto & a : actions) {
			a.second.updateDependencies(possibleDependencies);
		}
		for (auto & e : events) {
			e.second.updateDependencies(possibleDependencies);
		}
		for (auto & a : annuals) {
			a.second.updateDependencies(possibleDependencies);
		}
	}

	Project & Project::getSubproject(std::string name) {
		return subprojects[name];
	}


	std::set<std::string> Project::getPossibleDependents() const {
		std::set<std::string> result;
		for (Action const & a : actions) {
			result.insert(a.first);
		}
		for (Event const & e : events) {
			result.insert(e.first);
		}
		for (Annual const & a : annuals) {
			result.insert(a.first);
		}
		return result;
	}

	std::set<std::string> Project::getPossibleDependencies() const {
		std::set<std::string> result;
		for (Action const & a : actions) {
			result.insert(a.first);
		}
		for (Event const & e : events) {
			result.insert(e.first);
		}
		for (Subproject const & s : subprojects) {
			result.insert(s.first);
		}
		return result;
	}

	bool Project::isActionable() const {
		if (!actions.empty() || !habits.empty() || !events.empty() || !annuals.empty()) {
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
		if (!p.getHabits().empty()) {
			j.emplace("habits", p.getHabits());
		}
		if (!p.getEvents().empty()) {
			j.emplace("events", p.getEvents());
		}
		if (!p.getAnnuals().empty()) {
			j.emplace("annuals", p.getAnnuals());
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
		if (j.count("habits")) {
			p.setHabits(j.at("habits").get<Habits>());
		}
		if (j.count("events")) {
			p.setEvents(j.at("events").get<Events>());
		}
		if (j.count("annuals")) {
			p.setAnnuals(j.at("annuals").get<Annuals>());
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

	void accumulateHabits(Habits & h, Subproject const & sp) {
		Habits const & localHabits = sp.second.getHabits();
		h.insert(localHabits.begin(), localHabits.end());
		sp.second.accumulateFromSubprojects(h, accumulateHabits);
	}

	void accumulateEvents(Events & e, Subproject const & sp) {
		Events const & localEvents = sp.second.getEvents();
		e.insert(localEvents.begin(), localEvents.end());
		sp.second.accumulateFromSubprojects(e, accumulateEvents);
	}

	void accumulateAnnuals(Annuals & a, Subproject const & sp) {
		Annuals const & localAnnuals = sp.second.getAnnuals();
		a.insert(localAnnuals.begin(), localAnnuals.end());
		sp.second.accumulateFromSubprojects(a, accumulateAnnuals);
	}

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp) {
		if (!sp.second.isActionable() && !sp.second.isFrozen()) {
			sps.emplace(sp);
		}
		sp.second.accumulateFromSubprojects(sps, accumulateNonactionable);
	}

}
