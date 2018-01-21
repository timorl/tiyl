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

}
