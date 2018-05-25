#include"cli/Context.hpp"

namespace cli {

	Project const & Context::getProject(ProjectPath const & genealogy) const {
		Project * result = current;
		for (std::string const & childName : genealogy) {
			if (result->getSubprojects().count(childName) == 0) {
				return *result;
			}
			result = &(result->getSubproject(childName));
		}
		return *result;
	}


	bool Context::moveToChild(ProjectPath const & genealogy) {
		int depth = 0;
		for (std::string const & childName : genealogy) {
			if (current->getSubprojects().count(childName) == 0) {
				while (depth > 0) {
					moveUp();
					depth--;
				}
				return false;
			}
			parents.push(current);
			parentNames.push(currentName);
			current = &(current->getSubproject(childName));
			currentName = childName;
			depth++;
		}
		return true;
	}

	bool Context::moveToChild(std::string const & name) {
		return moveToChild(ProjectPath{name});
	}

	bool Context::moveUp() {
		if (parents.empty()) {
			return false;
		}
		current = parents.top();
		parents.pop();
		currentName = parentNames.top();
		parentNames.pop();
		return true;
	}

	void Context::moveUp(ProjectPath const & genealogy) {
		for (unsigned int i = 0; i < genealogy.size(); i++) {
			moveUp();
		}
	}

	void Context::moveTop() {
		current = &life;
		currentName = ROOT_NAME;
		parents = std::stack<Project *>();
		parentNames = std::stack<std::string>();
	}


	void Context::addMess(Mess const & m) {
		if (m.size() > 0) {
			current->addToMess(m);
			pendingChanges = true;
		}
	}

	void Context::addMess(std::string const & name) {
		current->addMess(name);
		pendingChanges = true;
	}

	void Context::delMess(std::string const & name) {
		current->delMess(name);
		pendingChanges = true;
	}

	void Context::delMess(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delMess(name);
			moveUp(genealogy);
		}
	}

	bool Context::addAction(Action && a) {
		if ( current->addAction(std::move(a)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::delAction(std::string const & name) {
		current->delAction(name);
		current->updateDependencies();
		pendingChanges = true;
	}

	void Context::delAction(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delAction(name);
			moveUp(genealogy);
		}
	}

	bool Context::addHabit(Habit && h) {
		if ( current->addHabit(std::move(h)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::doHabit(std::string const & name) {
		current->doHabit(name);
		pendingChanges = true;
	}

	void Context::doHabit(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			doHabit(name);
			moveUp(genealogy);
		}
	}

	void Context::delHabit(std::string const & name) {
		current->delHabit(name);
		pendingChanges = true;
	}

	void Context::delHabit(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delHabit(name);
			moveUp(genealogy);
		}
	}

	bool Context::addEvent(Event && e) {
		if ( current->addEvent(std::move(e)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::delEvent(std::string const & name) {
		current->delEvent(name);
		current->updateDependencies();
		pendingChanges = true;
	}

	void Context::delEvent(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delEvent(name);
			moveUp(genealogy);
		}
	}

	bool Context::addAnnual(Annual && a) {
		if ( current->addAnnual(std::move(a)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::delAnnual(std::string const & name) {
		current->delAnnual(name);
		pendingChanges = true;
	}

	void Context::delAnnual(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delAnnual(name);
			moveUp(genealogy);
		}
	}

	bool Context::addSubproject(Subproject && s) {
		if ( current->addSubproject(std::move(s)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::delSubproject(std::string const & name) {
		current->delSubproject(name);
		current->updateDependencies();
		pendingChanges = true;
	}

	void Context::delSubproject(ProjectPath const & genealogy, std::string const & name) {
		if (moveToChild(genealogy)) {
			delSubproject(name);
			moveUp(genealogy);
		}
	}

	bool Context::addDependency(std::string what, std::string onWhat) {
		if ( current->addDependency(what, onWhat) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::freeze() {
		current->setFrozen(true);
		pendingChanges = true;
	}

	void Context::thaw() {
		current->setFrozen(false);
		pendingChanges = true;
	}

}
