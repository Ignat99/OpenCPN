#ifndef MYSQLCPPAPI_STRING_UTIL_H
#define MYSQLCPPAPI_STRING_UTIL_H

#include <cctype>
#include <string>

namespace mysqlcppapi
{

/// Escape a string for inclusion in an SQL statement.
std::string escape(const std::string& input);

void strip (std::string& s); // Strips blanks at left and right ends

inline void str_to_upr (std::string& s) { // Changes case of string to upper
	for (unsigned int cnt=0; cnt < s.length(); cnt++) {
		char c = s[cnt]; s[cnt]=toupper(c);
	}
}

inline void str_to_lwr (std::string& s) { // Changes case of string to lower
	for (unsigned int cnt=0; cnt < s.length(); cnt++) {
		char c = s[cnt]; s[cnt]=tolower(c);
	}
}

inline void strip_all_blanks (std::string& s) { // Removes all blanks
	for (unsigned int counter=0;counter < s.size();counter++)
		if (s[counter] == ' ') { s.erase(counter,1); counter--;}
}

inline void strip_all_non_num (std::string& s) { // Removes all non-numerics
	for (unsigned int counter=0;counter < s.size();counter++)
		if (!isdigit(s[counter])) { s.erase(counter,1); counter--;}
}

} //namespace

#endif  //MYSQLCPPAPI_STRING_UTIL_H
