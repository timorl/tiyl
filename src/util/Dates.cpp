#include"util/Dates.hpp"

#include<sstream>
#include<iomanip>

namespace util {

	using Days = std::chrono::duration<int, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;

	std::string dateToString(Date const & t) {
		std::time_t tt = std::chrono::system_clock::to_time_t(t);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M");
		std::string s;
		std::getline(ss, s);
		return s;
	}

	Date stringToDate(std::string const & s) {
		std::tm tm = {};
		std::stringstream ss(s);
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
		tm.tm_isdst = -1;
		if (ss.fail()) {
			return maxDate();
		}
		return std::chrono::system_clock::from_time_t(std::mktime(&tm));
	}

	std::string annualToString(Date const & t) {
		std::time_t tt = std::chrono::system_clock::to_time_t(t);
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%m-%d");
		std::string s;
		std::getline(ss, s);
		return s;
	}

	Date stringToAnnual(std::string const & s) {
		std::time_t  tt = std::chrono::system_clock::to_time_t(now());
		std::tm tm = *std::localtime(&tt);
		tm.tm_sec = 0;
		tm.tm_min = 0;
		tm.tm_hour = 0;
		std::stringstream ss(s);
		ss >> std::get_time(&tm, "%m-%d");
		if (ss.fail()) {
			return maxDate();
		}
		Date result = std::chrono::system_clock::from_time_t(std::mktime(&tm));
	 while (daysSince(result) > 0) {
			tm.tm_year = tm.tm_year + 1;
			result = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		}
		return result;
	}

	Date now() {
		return std::chrono::system_clock::now();
	}

	Date maxDate() {
		return std::chrono::time_point<std::chrono::system_clock>::max();
	}

	int daysBetween(Date const & start, Date const & end) {
		return std::chrono::duration_cast<Days>(end - start).count();
	}

	int daysSince(Date const & t) {
		return daysBetween(t, now());
	}

}
