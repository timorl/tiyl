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

	bool Project::addTodo(Todo && t) {
		if (todos.count(t)) {
			return false;
		}
		todos[t] = t;
		return true;
	}

	void Project::delTodo(std::string const & name) {
		todos.erase(name);
	}


	Project & Project::getSubproject(std::string name) {
		return subprojects[name];
	}

	bool Project::isActionable() const {
		if (!todos.empty()) {
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

	void to_json(json & j, Project const & p) {
		j = {{"description", p.getDescription()}};
		if (p.getSubprojects().size()) {
			j.emplace("subprojects", p.getSubprojects());
		}
		if (p.getTodos().size()) {
			j.emplace("todos", p.getTodos());
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
		if (j.count("todos")) {
			p.setTodos(j.at("todos").get<TodoList>());
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
		m.insert(localMess.begin(), localMess.end());
		sp.second.accumulateFromSubprojects(m, accumulateMess);
	}

	void accumulateTodos(TodoList & a, Subproject const & sp) {
		TodoList const & localTodos = sp.second.getTodos();
		a.insert(localTodos.begin(), localTodos.end());
		sp.second.accumulateFromSubprojects(a, accumulateTodos);
	}

	void accumulateNonactionable(Subprojects & sps, Subproject const & sp) {
		if (sp.second.getTodos().empty()) {
			sps.emplace(sp);
		}
		sp.second.accumulateFromSubprojects(sps, accumulateNonactionable);
	}

}
