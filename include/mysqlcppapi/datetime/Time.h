#ifndef MYSQLCPPAPI_Time_h
#define MYSQLCPPAPI_Time_h

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include "mysqlcppapi/datetime/time_base.h"

#include "mysqlcppapi/ColData.h"

namespace mysqlcppapi
{

class Time : public time_base, public DTbase<Time>
{
public:
  Time();
  Time(const std::string& str);
  Time(const ColData& str);
  virtual ~Time();

  short int compare(const Time& other) const;
};


inline std::ostream& operator << (std::ostream& s, const Time& d)
{
  return d.out_stream(s);
}

inline Time::Time(const ColData& str)
{
  convert(str.get_string());
}

inline Time::Time(const std::string& str)
{
  convert(str);
}

} //namespace


#endif //MYSQLCPPAPI_Time_h

