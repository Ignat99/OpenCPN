#ifndef MYSQLCPPAPI_EX_BADQUERY_NOTENOUGHPARAMETERS_H
#define MYSQLCPPAPI_EX_BADQUERY_NOTENOUGHPARAMETERS_H
#include <string>

#include "mysqlcppapi/exceptions/ex_BadQuery.h"

namespace mysqlcppapi
{

/// Exception thrown when a Bad Query is encountered
class ex_BadQuery_NotEnoughParameters : public ex_BadQuery
{
public:
  ex_BadQuery_NotEnoughParameters() throw();
  ex_BadQuery_NotEnoughParameters(const std::string& src) throw();
  ex_BadQuery_NotEnoughParameters(const ex_BadQuery_NotEnoughParameters& src) throw();
  ex_BadQuery_NotEnoughParameters& operator=(const ex_BadQuery_NotEnoughParameters& src);
  virtual ~ex_BadQuery_NotEnoughParameters() throw();

};

} //namespace

#endif //MYSQLCPPAPI_EX_BADQUERY_NOTENOUGHPARAMETERS_H
