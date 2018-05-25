#include "catch.hpp"
#include "../Parsing.hpp"

using namespace util;

TEST_CASE("Single word", "[tokenizing]") {
	std::string input = "word";
	REQUIRE(tokenize(input) == std::vector<std::string>{"word"});
}

TEST_CASE("Single quoted word", "[tokenizing]") {
	std::string input = "\"word\"";
	REQUIRE(tokenize(input) == std::vector<std::string>{"word"});
}

TEST_CASE("Couple words", "[tokenizing]") {
	std::string input = "This is a couple of words";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with quotations", "[tokenizing]") {
	std::string input = "This \"is\" a \"couple\" of words";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with phrases", "[tokenizing]") {
	std::string input = "This is \"a couple\" of words";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces", "[tokenizing]") {
	std::string input = "   This   is a    couple   of   words    ";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces and quotations", "[tokenizing]") {
	std::string input = "   This   \"is\" a    \"couple\"   of   words    ";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces, quotations and phrases", "[tokenizing]") {
	std::string input = "   This   is \"a    couple\"   of   words    ";
	REQUIRE(tokenize(input) == std::vector<std::string>{"This", "is", "a    couple", "of", "words"});
}

TEST_CASE("Single name", "[path, tokenizing]") {
	std::string input = "Name";
	REQUIRE(tokenizePath(input) == std::vector<std::string>{"Name"});
}

TEST_CASE("Single path", "[path, tokenizing]") {
	std::string input = "Path/";
	REQUIRE(tokenizePath(input) == std::vector<std::string>{"Path/"});
}

TEST_CASE("Path with name", "[path, tokenizing]") {
	std::string input = "Path/To Something/Name";
	REQUIRE(tokenizePath(input) == std::vector<std::string>{"Path/", "To Something/", "Name"});
}

TEST_CASE("Path without name", "[path, tokenizing]") {
	std::string input = "Path/To Something/";
	REQUIRE(tokenizePath(input) == std::vector<std::string>{"Path/", "To Something/"});
}

