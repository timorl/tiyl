#include "catch.hpp"
#include "../Dates.hpp"

using namespace util;

TEST_CASE("Encoding and decoding dates", "[dates]") {
	std::string someDate = "1998-03-13 13:48";
	REQUIRE(dateToString(stringToDate(someDate)) == someDate);
}

TEST_CASE("Encoding and decoding dates with DST", "[dates]") {
	std::string someDate = "1998-09-13 13:48";
	REQUIRE(dateToString(stringToDate(someDate)) == someDate);
}
