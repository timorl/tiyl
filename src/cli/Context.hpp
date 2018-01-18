#ifndef TIYL_CLI_CONTEXT_HPP
#define TIYL_CLI_CONTEXT_HPP
#include<string>
#include<stack>

#include"projects/Project.hpp"
#include"projects/Mess.hpp"

namespace cli {

	using Project = projects::Project;
	using Mess = projects::Mess;

	const std::string ROOT_NAME("Life");

	class Context {
		public:
			Context(Project && life, Mess && mess) :
				life(life),
				mess(mess),
				current(&(this->life)),
				currentName(ROOT_NAME),
				lastResult(0)
		{}

			Mess const & getMess() const { return mess; }

			Project const & getProject() const { return *current; }

			bool moveToChild(std::string childName);

			bool moveUp();

			void moveTop();

			void setLastResult(int r) { lastResult = r; }

			int getLastResult() { return lastResult; }
		private:
			Project life;
			Mess mess;
			Project * current;
			std::string currentName;
			std::stack<Project *> parents;
			std::stack<std::string> parentNames;

			int lastResult;
	};

}
#endif
