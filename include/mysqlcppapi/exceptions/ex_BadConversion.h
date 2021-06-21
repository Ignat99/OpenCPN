#ifndef MYSQLCPPAPI_EX_BADCONVERSION__KK
#define MYSQLCPPAPI_EX_BADCONVERSION__KK

#include "mysqlcppapi/exceptions/ex_base.h"

namespace mysqlcppapi
{

/// Exception structure thrown when a bad conversion takes place
class ex_BadConversion : public ex_base
{
public:

  ex_BadConversion() throw();
  ex_BadConversion(const std::string& strTypeName, const std::string& strData, size_t sizeRetrieved, size_t sizeActual) throw();
  ex_BadConversion(const ex_BadConversion& src) throw();
  ex_BadConversion& operator=(const ex_BadConversion& src);
  virtual ~ex_BadConversion() throw();
  
  virtual std::string get_TypeName() const;
  virtual std::string get_Data() const;
  virtual size_t get_SizeRetrieved() const;
  virtual size_t get_SizeActual() const;
  
protected:
  std::string  m_strTypeName;
  std::string m_strData;
  size_t m_sizeRetrieved;  
  size_t m_sizeActual;
};

} //namespace

#endif //__EX_BADCONVERSION__KK
