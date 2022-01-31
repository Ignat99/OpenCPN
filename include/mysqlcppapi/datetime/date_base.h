#ifndef MYSQLCPPAPI_DATE_BASE_H
#define MYSQLCPPAPI_DATE_BASE_H

#include "mysqlcppapi/datetime/datetime_base.h"

namespace mysqlcppapi
{

class date_base : virtual public datetime_base
{
public:

  short int year;

  typedef short int tiny_int;
  tiny_int  month;
  tiny_int  day;

  std::ostream& out_stream(std::ostream&) const;
  std::string::size_type convert(const std::string&);
  
protected:
  short int compare(const date_base *other) const;
};

} //namespace

#endif //MYSQLCPPAPI_DATE_BASE_H

