#ifndef MYSQLCPPAPI_datetime_base_h
#define MYSQLCPPAPI_datetime_base_h

#include "mysqlcppapi/datetime/stream2string.h"

#include <string>
#include <iosfwd>

namespace mysqlcppapi
{

class datetime_base
{
public:
  datetime_base();
  virtual ~datetime_base();
  
  virtual std::ostream& out_stream(std::ostream&) const = 0;

  operator std::string();
};

inline datetime_base::operator std::string ()
{
  return stream2string<std::string>(*this);
}

template <class T>
class DTbase
{
protected:
  virtual ~DTbase() {}

public:
  virtual short int compare(const T &other) const = 0;

  bool operator == (const T &other) const
  {
    return !compare(other);
  }
  
  bool operator != (const T &other) const
  {
    return compare(other);
  }
  
  bool operator <  (const T &other) const
  {
    return compare(other) < 0;
  }
  
  bool operator <= (const T &other) const
  {
    return compare(other) <= 0;
  }
  
  bool operator >  (const T &other) const
  {
    return compare(other) > 0;
  }
  
  bool operator >= (const T &other) const
  {
    return compare(other) >= 0;
  }
};


} //namespace

#endif //MYSQLCPPAPI_datetime_base_h

