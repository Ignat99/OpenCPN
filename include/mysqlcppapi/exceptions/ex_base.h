// ex_base.h: interface for the ex_base class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MYSQLCPPAPI_EX_BASE_H
#define MYSQLCPPAPI_EX_BASE_H

#include <string>
#include <exception>

namespace mysqlcppapi
{

class ex_base : public std::exception  
{
public:
  ex_base() throw();
  ex_base(const std::string& src) throw();
  ex_base(const ex_base& src) throw();
  ex_base& operator=(const ex_base& src);
  virtual ~ex_base() throw();

  virtual const char* what() const throw();


protected:
  std::string m_strMessage;

};

} //namespace

#endif // MYSQLCPPAPI_EX_BASE_H
