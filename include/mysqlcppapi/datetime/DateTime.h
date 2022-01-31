#ifndef MYSQLCPPAPI_DATETIME_H
#define MYSQLCPPAPI_DATETIME_H

#include "mysqlcppapi/datetime/Time.h"
#include "mysqlcppapi/datetime/Date.h"


#include <string>
#include <sstream>
#include <iostream>

namespace mysqlcppapi
{

/// A combination of Date and Time for holding mysql DateTime's
class DateTime : public date_base, public time_base, public DTbase<DateTime>
{
public:
  DateTime();
  DateTime(const std::string &str);
  DateTime(const ColData &str);
  virtual ~DateTime();

  short int compare(const DateTime& other) const;

  std::ostream& out_stream(std::ostream&) const;
  std::string::size_type convert(const std::string&);
};

inline std::ostream& operator << (std::ostream& s, const DateTime& d)
{
  return d.out_stream(s);
}


inline DateTime::DateTime(const ColData& str)
{
  convert(str.c_str());
}

inline DateTime::DateTime(const std::string& str)
{
  convert(str.c_str());
}

} //namespace

#endif //MYSQLCPPAPI_DATETIME_H

