#ifndef MYSQLCPPAPI_COLDATA_H
#define MYSQLCPPAPI_COLDATA_H

#include "mysqlcppapi_internal.h"

#include "mysqlcppapi/fields/FieldType.h"

#include "mysqlcppapi/null.h"
#include "mysqlcppapi/exceptions/ex_BadConversion.h"

#include "mysqlcppapi/string_util.h"
#include "mysqlcppapi/convert.h"

#include <typeinfo>
#include <string>

#define oprsw(opr, other, conv) \
  template<class T_Str> \
  inline other operator opr(ColData_Generic<T_Str> x, other y) \
    {return (conv)x opr y;} \
  template<class T_Str> \
  inline other operator opr(other x, ColData_Generic<T_Str> y) \
    {return x opr (conv)y;}

#define operator_binary(other, conv) \
  oprsw(+, other, conv) \
  oprsw(-, other, conv) \
  oprsw(*, other, conv) \
  oprsw(/, other, conv) 

#define operator_binary_int(other, conv) \
  operator_binary(other, conv) \
  oprsw(%, other, conv) \
  oprsw(&, other, conv) \
  oprsw(^, other, conv) \
  oprsw(|, other, conv) \
  oprsw(<<, other, conv) \
  oprsw(>>, other, conv) 

#define operator_conversion(T) operator T() const { return conv<T>(); }

namespace mysqlcppapi
{

//! with_class = ColData_Generic


//: Base class for auto-converting column data.  Do not use directly. 
//
// A smart string. It will automatically convert it self to any of the
// basic C types. 
//
// When used with binary operators it will
// automatically convert it self to the type used on the other side of
// the operator if it is a basic type.
//
// However, be careful when using it with binary operators as. 
// 
// MysqlStr("12.86") + 2
// 
// will return 14 because 2 is an integer. What you wanted to say was 
//
// MysqlStr("12.86") + 2.0
//
// If this type of thing scares you define the micro NO_BINARY_OPERS
// to turn of this behavior.
//
// This class also has some basic information about the type of data
// stored in it.
//
// <bf>Do not use this class directly.</bf>
//  Use the typedef ColData or MutableColData instead.
template <class T_Str>
class ColData_Generic : public T_Str
{
public:
  ColData_Generic(bool isNull) 
    : m_bNull(isNull)
  {
  }
  
  ColData_Generic(const std::string& str, bool isNull = false)
    : T_Str(str), buf(str), m_bNull(isNull)
  {
  }

  template<class Type>
  Type conv(Type dummy) const { return conv<Type>(); }

  template<class Type>
  Type conv() const;

  //!dummy: operator TYPE() const;
  //: Converts the column data to TYPE.
  // If all the characters are not read during the conversion to TYPE it
  // will through ex_BadConversion.
  //
  // TYPE is defined for all the built-in types.
  //
  
#if 0
  void is_null()
  {
    m_bNull = true;
  }
#endif
  
  inline bool is_null() const
  {
    return m_bNull;
  }

  inline const std::string& get_string() const
  {
    return buf;
  }
  
  operator const char*() const
  {
    return buf.c_str();
  }
  
  operator_conversion(signed char)
  operator_conversion(unsigned char)
  operator_conversion(int)
  operator_conversion(unsigned int)
  operator_conversion(short)
  operator_conversion(unsigned short)
  operator_conversion(long)
  operator_conversion(unsigned long)

#ifndef NO_LONG_LONGS
  operator_conversion(long long)
  operator_conversion(unsigned long long)
#endif
  operator_conversion(float)
  operator_conversion(double)

  template <class T, class B> operator Null<T,B>() const;
  
protected:
  //FieldType _type;
  std::string buf;
  bool m_bNull;
};

//: The Type that is returned by constant rows
typedef ColData_Generic<std::string> ColData;

//: The Type that is returned by mutable rows
typedef ColData_Generic<std::string> MutableColData;



//These are macros:
operator_binary(float, double)
operator_binary(double, double)

operator_binary_int(char,long int)
operator_binary_int(int, long int)
operator_binary_int(short int, long int)
operator_binary_int(long int, long int)

operator_binary_int(unsigned char, unsigned long int)
operator_binary_int(unsigned int, unsigned long int)
operator_binary_int(unsigned short int, unsigned long int)
operator_binary_int(unsigned long int, unsigned long int)

#ifndef NO_LONG_LONGS
operator_binary_int(long long int, long long int)
operator_binary_int(unsigned long long int, unsigned long long int)
#endif 

template <class T_Str> template <class T, class B> 
ColData_Generic<T_Str>::operator Null<T,B>() const {
  if((*this)[0] == 'N' && (*this)[1] == 'U' && 
     (*this)[2] == 'U' && (*this)[3] == 'L' && T_Str::size() == 4)
    return Null<T,B>(null);
  else return Null<T,B>(conv<T>());
}


template <class T_Str> template<class Type> 
Type ColData_Generic<T_Str>::conv() const
{
  std::string strbuf(buf);
  strip_all_blanks(strbuf);
  size_t len = strbuf.size();
  const char *str = strbuf.c_str();
  const char *end = str;
  Type num = mysql_convert<Type>(str, end);

  if(*end == '.')
  {
    end++;
    for(;*end == '0'; end++);
  }

  if(*end != '\0' && end != NULL )
  {
    throw ex_BadConversion(typeid(Type).name(), T_Str::c_str(), end - str, len);
  }

  return num;
}

} //namespace

#undef operator_conversion
#undef operator_binary_int
#undef operator_binary
#undef oprsw

#endif //MYSQLCPPAPI_COLDATA_H
