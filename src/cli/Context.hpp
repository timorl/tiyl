#ifndef TIYL_CLI_CONTEXT_HPP
#define TIYL_CLI_CONTEXT_HPP
#include<string>
#include<stack>

#include"projects/Project.hpp"
#include"projects/Todo.hpp"
#include"projects/Mess.hpp"

namespace cli {

	using Project = projects::Project;
	using Subproject = std::pair<std::string, Project>;
	using Todo = projects::Todo;
	using Mess = projects::Mess;

	const std::string ROOT_NAME("Life");

	class Context {
		public:
			Context(Project && life) :
				life(life),
				current(&(this->life)),
				currentName(ROOT_NAME),
				lastResult(0),
				pendingChanges(false)
			{}

			Project const & getProject() const { return *current; }

			Project const & getMainProject() const { return life; }

			std::string const & getCurrentName() const { return currentName; }


			bool moveToChild(std::string childName);

			bool moveUp();

			void moveTop();


			void addMess(Mess const & m);

			void addMess(std::string const & name);

			void delMess(std::string const & name);

			bool addTodo(Todo && t);

			void delTodo(std::string const & name);

			bool addSubproject(Subproject && s);

			void delSubproject(std::string const & name);

			void freeze();

			void thaw();


			void setLastResult(int r) { lastResult = r; }

			int getLastResult() const { return lastResult; }

			bool modified() const { return pendingChanges; }

			void resetModified() { pendingChanges = false; }
		private:
			Project life;
			Project * current;
			std::string currentName;
			std::stack<Project *> parents;
			std::stack<std::string> parentNames;

			int lastResult;
			bool pendingChanges;
	};

}
#endif
