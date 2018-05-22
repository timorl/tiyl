#include "catch.hpp"
#include "../Tokenizing.hpp"

using namespace cli;

TEST_CASE("Single word", "[tokenizing]") {
	std::string input = "word";
	REQUIRE(tokenize(input) == Arguments{"word"});
}

TEST_CASE("Single quoted word", "[tokenizing]") {
	std::string input = "\"word\"";
	REQUIRE(tokenize(input) == Arguments{"word"});
}

TEST_CASE("Couple words", "[tokenizing]") {
	std::string input = "This is a couple of words";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with quotations", "[tokenizing]") {
	std::string input = "This \"is\" a \"couple\" of words";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with phrases", "[tokenizing]") {
	std::string input = "This is \"a couple\" of words";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces", "[tokenizing]") {
	std::string input = "   This   is a    couple   of   words    ";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces and quotations", "[tokenizing]") {
	std::string input = "   This   \"is\" a    \"couple\"   of   words    ";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a", "couple", "of", "words"});
}

TEST_CASE("Couple words with lots of spaces, quotations and phrases", "[tokenizing]") {
	std::string input = "   This   is \"a    couple\"   of   words    ";
	REQUIRE(tokenize(input) == Arguments{"This", "is", "a    couple", "of", "words"});
}

