#ifndef MYSQLCPPAPI_EX_LOCKED_H
#define MYSQLCPPAPI_EX_LOCKED_H
#include <string>

#include "mysqlcppapi/exceptions/ex_base.h"

namespace mysqlcppapi
{

/// Exception thrown when a Bad Query is encountered
class ex_Locked : public ex_base
{
public:
  ex_Locked() throw();
  ex_Locked(const std::string& src) throw();
  ex_Locked(const ex_Locked& src) throw();
  ex_Locked& operator=(const ex_Locked& src);
  virtual ~ex_Locked() throw();

};

} //namespace

#endif //MYSQLCPPAPI_EX_LOCKED_H
