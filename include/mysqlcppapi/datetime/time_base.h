#ifndef MYSQLCPPAPI_time_base_h
#define MYSQLCPPAPI_time_base_h

#include "mysqlcppapi/datetime/datetime_base.h"

namespace mysqlcppapi
{

class time_base : virtual public datetime_base
{
public:
  time_base();
  virtual ~time_base();

  typedef short int tiny_int;
  tiny_int hour;
  tiny_int minute;  
  tiny_int second;

  std::ostream& out_stream(std::ostream& str) const;
  std::string::size_type convert(const std::string& str);
  
protected:
  short int compare(const time_base* other) const;
};  

} //namespace


#endif //MYSQLCPPAPI_time_base_h

