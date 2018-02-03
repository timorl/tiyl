#include"cli/Context.hpp"

namespace cli {

	bool Context::moveToChild(std::string childName) {
		if (current->getSubprojects().count(childName) == 0) {
			return false;
		}
		parents.push(current);
		parentNames.push(currentName);
		current = &(current->getSubproject(childName));
		currentName = childName;
		return true;
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

	bool Context::addAction(Action && a) {
		if ( current->addAction(std::move(a)) ) {
			pendingChanges = true;
			return true;
		}
		return false;
	}

	void Context::delAction(std::string const & name) {
		current->delAction(name);
		pendingChanges = true;
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

	void Context::delHabit(std::string const & name) {
		current->delHabit(name);
		pendingChanges = true;
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
		pendingChanges = true;
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
