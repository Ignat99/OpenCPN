#ifndef MYSQLCPPAPI_EX_BADNULLCONVERSION__KK
#define MYSQLCPPAPI_EX_BADNULLCONVERSION__KK

#include "mysqlcppapi/exceptions/ex_base.h"

namespace mysqlcppapi
{

/// Thrown when trying to convert a *Null* value into a type which it can't convert to.
class ex_BadNullConversion : public ex_base
{
public:

  ex_BadNullConversion() throw();
  ex_BadNullConversion(const ex_BadNullConversion& src) throw();
  ex_BadNullConversion& operator=(const ex_BadNullConversion& src);
  virtual ~ex_BadNullConversion() throw();
};

} //namespace

#endif //MYSQLCPPAPI_EX_BADNULLCONVERSION__KK
