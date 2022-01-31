#ifndef MYSQLCPPAPI_DATE_H
#define MYSQLCPPAPI_DATE_H

#include "mysqlcppapi/mysqlcppapi_internal.h"
#include "mysqlcppapi/datetime/date_base.h"
#include "mysqlcppapi/ColData.h"



namespace mysqlcppapi
{

class Date : public date_base, public DTbase<Date>
{
public:
  Date();
  Date(const std::string& str);
  Date(const ColData& str);
  virtual ~Date();

  short int compare(const Date& other) const;
};

inline std::ostream& operator << (std::ostream& s, const Date& d)
{
  return d.out_stream(s);
}


} //namespace

#endif //MYSQLCPPAPI_DATE_H

