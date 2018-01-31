#include"cli/Pretty.hpp"

namespace cli {

	const std::string codeStart("\033[");
	const std::string codeEnd("m");

	const int NORMALIZE = 0;
	const int RED = 31;
	const int CYAN = 36;
	const int BRIGHT_BLACK = 90;
	const int BRIGHT_WHITE = 97;

	inline std::string code(int c) {
		return codeStart + std::to_string(c) + codeEnd;
	}

	std::string lessVisible(std::string input) {
		return code(BRIGHT_BLACK) + input + code(NORMALIZE);
	}

	std::string brightWhite(std::string input) {
		return code(BRIGHT_WHITE) + input + code(NORMALIZE);
	}

	std::string red(std::string input) {
		return code(RED) + input + code(NORMALIZE);
	}

	std::string cyan(std::string input) {
		return code(CYAN) + input + code(NORMALIZE);
	}

}
