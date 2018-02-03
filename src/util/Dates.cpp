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
		return std::chrono::system_clock::from_time_t(std::mktime(&tm));
	}

	Date now() {
		return std::chrono::system_clock::now();
	}

	int daysBetween(Date const & start, Date const & end) {
		return std::chrono::duration_cast<Days>(end - start).count();
	}

	int daysSince(Date const & t) {
		return daysBetween(t, now());
	}

}
