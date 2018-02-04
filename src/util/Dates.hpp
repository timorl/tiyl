#ifndef TIYL_UTIL_DATES_HPP
#define TIYL_UTIL_DATES_HPP
#include<string>
#include<chrono>

namespace util {

	using Date = std::chrono::system_clock::time_point;

	std::string dateToString(Date const & t);

	Date stringToDate(std::string const & s);

	Date now();

	Date maxDate();

	int daysBetween(Date const & start, Date const & end);

	int daysSince(Date const & t);

}
#endif
