#ifndef MYSQLCPPAPI_BAD_QUERY_EXCEPT__KK
#define MYSQLCPPAPI_BAD_QUERY_EXCEPT__KK
#include <string>

#include "mysqlcppapi/exceptions/ex_base.h"

namespace mysqlcppapi
{

/// Exception thrown when a Bad Query is encountered
class ex_BadQuery : public ex_base
{
public:
  ex_BadQuery() throw();
  ex_BadQuery(const std::string& src) throw();
  ex_BadQuery(const ex_BadQuery& src) throw();
  ex_BadQuery& operator=(const ex_BadQuery& src);
  virtual ~ex_BadQuery() throw();

};

} //namespace

#endif  //MYSQLCPPAPI_BAD_QUERY_EXCEPT__KK
